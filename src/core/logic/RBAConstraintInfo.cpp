/// 制約式情報クラス定義ファイル

#include <algorithm>
#include "RBAAllocatable.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpression.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAConstraintInfo::setExpression(const RBAExpression* const expression)
{
  expression_ = expression;
}

const RBAExpression*
RBAConstraintInfo::getExpression() const
{
  return expression_;
}

void RBAConstraintInfo::addOperandAllocatable(const RBAAllocatable* const operandAllocatable)
{
  static_cast<void>(operandAllocatable_.insert(operandAllocatable));
}

void RBAConstraintInfo::setResult(const RBAExecuteResult result)
{
  result_ = result;
}

RBAConstraintInfo*
RBAConstraintInfo::getChild(const std::uint32_t index) const
{
  const std::size_t requiredSize {static_cast<std::size_t>(index + 1U)};
  if (children_.size() < requiredSize) {
    children_.resize(requiredSize, std::make_unique<RBAConstraintInfo>());
  }
  // 範囲外アクセスしないので、コスト面を考え、atではなく[]を使用する
  return children_[static_cast<std::size_t>(index)].get();
}

void RBAConstraintInfo::setChild(const std::shared_ptr<RBAConstraintInfo> info)
{
  // この関数はlet式で使用し、let式では、評価のたびに新しいConstraintInfoを生成する。
  // そのため、addだと、調停毎にchildrenが追加されてしまうので、setで調停毎にchildrenを設定している
  children_ = { info };
}

void RBAConstraintInfo::addTrueAllocatable(const RBAAllocatable* const allocatable)
{
  static_cast<void>(trueAllocatables_.insert(allocatable));
}

void RBAConstraintInfo::addFalseAllocatable(const RBAAllocatable* const allocatable)
{
  static_cast<void>(falseAllocatables_.insert(allocatable));
}

void RBAConstraintInfo::addTrueAllocatableFromOperand()
{
  for (const auto& c : children_) {
    for (const auto& a : c->operandAllocatable_) {
      static_cast<void>(trueAllocatables_.insert(a));
    }
  }
}

void RBAConstraintInfo::addFalseAllocatableFromOperand()
{
  for (const auto& c : children_) {
    for (const auto& a : c->operandAllocatable_) {
      static_cast<void>(falseAllocatables_.insert(a));
    }
  }
}

void RBAConstraintInfo::clearFalseAllocatable()
{
  falseAllocatables_.clear();
}

/// True/Falseを反転させるか
/// @return
bool RBAConstraintInfo::isRevert() const
{
  if ((expression_ != nullptr)
      && expression_->isModelElementType(RBAModelElementType::NotOperator)) {
    return true;
  }
  return false;
}

bool RBAConstraintInfo::isSizeOperator() const
{
  if ((expression_ != nullptr)
      && (expression_->isModelElementType(RBAModelElementType::SizeOperator))) {
    return true;
  }
  return false;
}

const bool RBAConstraintInfo::isImplies() const
{
  if ((expression_ != nullptr)
      && (expression_->isModelElementType(RBAModelElementType::ImpliesOperator)
          || expression_->isModelElementType(RBAModelElementType::IfStatement))) {
    return true;
  }
  return false;
}

void RBAConstraintInfo::clear()
{
  for (const std::shared_ptr<RBAConstraintInfo>& child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // 【ルールに逸脱している内容】
    // clear()を再帰呼び出ししている
    // 【ルールを逸脱しても問題ないことの説明】
    // 制約式ツリーの各ノード毎にConstraintInfoは作成される。
    // 制約式ツリーはモデルファイルに書かれた制約式によって決定され、その深さは有限である。
    // そのため、スタックオーバーフローすることはなく、問題無い
    child->clear();
  }
  result_ = RBAExecuteResult::SKIP;
  exceptionBeforeArbitrate_ = false;
  trueAllocatables_.clear();
  falseAllocatables_.clear();
  operandAllocatable_.clear();
}

bool RBAConstraintInfo::isExceptionBeforeArbitrate() const
{
  return exceptionBeforeArbitrate_;
}

void RBAConstraintInfo::setExceptionBeforeArbitrate(
    const bool exceptionBeforeArbitrate)
{
  exceptionBeforeArbitrate_ = exceptionBeforeArbitrate;
}

bool RBAConstraintInfo::needsReRearbitrationFor(
    const RBAAllocatable* const allocatable) const
{
  bool result {false};
  if (children_.empty() == false) {
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        if (children_.front()->isExceptionBeforeArbitrate()) {
          result = children_.back()->needsReRearbitrationFor(allocatable);
        }
        break;
      case RBAModelElementType::IfStatement:
        if (children_.front()->isExceptionBeforeArbitrate()) {
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          // 【ルールに逸脱している内容】
          // Function '::rba::RBAConstraintInfo::needsReRearbitrationFor=(_,p={c::rba::RBAAllocatable})' is recursive.
          // 【ルールを逸脱しても問題ないことの説明】
          // 機能として再帰呼び出しが必要なため
          result = children_.back()->needsReRearbitrationFor(allocatable);
        }
        break;
      default:
        for (const auto& child : children_) {
          result = (result || child->needsReRearbitrationFor(allocatable));
        }
        result =
            (result || (trueAllocatables_.find(allocatable)  != trueAllocatables_.end())
                    || (falseAllocatables_.find(allocatable) != falseAllocatables_.end()));
        break;
    }
  }
  return result;
}

bool RBAConstraintInfo::needsRearbitrationFor(const RBAAllocatable* const allocatable,
                                              bool isImplies) const
{
  bool result {false};  // 再調停要否
  if (children_.empty() == false) {
    // 制約式の構文がImpliesOperatorのとき、
    // 制約式の構文がIfStatementのとき、
    // 制約式の構文が上記以外のとき、
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        // 含意の左辺がtrue、且つ、左辺に調停中アロケータブルが含まれているときは、再調停要と判定
        // 含意の左辺がtrue、且つ、左辺にアロケータブルの状態参照式が含まれているときは、再調停不要と判定
        if (children_.front()->isTrue()) {
          if (children_.front()->contains(allocatable)) {
            result = true;
          } else {
            if (children_.front()->contains(nullptr)) {
              isImplies = true;
            }
            result = (result || children_.back()->needsRearbitrationFor(allocatable,
                      isImplies));
          }
        }
        break;
      case RBAModelElementType::IfStatement:
        // IF条件に調停中アロケータブルが含まれているときは、再調停要と判定
        // IF条件にアロケータブルの状態参照式が含まれているときは、再調停不要と判定
        // IF条件にアロケータブルの状態参照式が含まれていないときは、子構文を探索;
        if (children_.front()->contains(allocatable)) {
          result = true;
        } else {
          if (children_.front()->contains(nullptr)) {
            isImplies = true;
          }
          result = (result || children_.back()->needsRearbitrationFor(allocatable,
                                                                      isImplies));
        }
        break;
      default:
        for (const auto& child : children_) {
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          // 【ルールに逸脱している内容】
          // Function '::rba::RBAConstraintInfo::needsRearbitrationFor=(_,p={c::rba::RBAAllocatable},_o)' is recursive. 
          // 【ルールを逸脱しても問題ないことの説明】
          // 機能として再帰呼び出しが必要なため
          result = (result || child->needsRearbitrationFor(allocatable, isImplies));
        }
        // 制約式にIF、または、含意を含まない、あるいは
        // 親構文のIF条件、または、親構文の含意の左辺に、アロケータブルの状態参照式が含まれていないとき、
        // 調停中アロケータブルが含まれているときは、再調停要と判定
        if (!isImplies && contains(allocatable)) {
          result = true;
        }
        break;
    }
  }
  return result;
}

/// @brief 右辺をfalseにしたアロケータブルを収集する
/// @details
/// ・例外が発生していれば、収集しない
/// ・expression_がnullptrの場合
/// ・expression_が含意の場合
///  ・左辺が成立しており、左辺にアロケータブル状態に影響を受ける条件があった場合、
///    右辺をfalseにした要因となったアロケータブルを収集する
///  ・左辺が成立しており、左辺にアロケータブル状態に影響を受ける条件がない場合、
///    右辺に対して本関数をコールする。※含意またはIFのnestに対応するため
/// ・expression_がIFの場合
///  ・左辺にアロケータブル状態に影響を受ける条件があった場合、
///    右辺をfalseにした要因となったアロケータブルを収集する
///  ・左辺にアロケータブル状態に影響を受ける条件がない場合、
///    右辺に対して本関数をコールする。※含意またはIFのnestに対応するため
/// ・expression_が否定の場合
///  ・左辺に対してisNotを反転した本関数をコールする。※含意またはIFが子に存在する場合に対応するため
/// ・expression_が上記の場合
///  ・子ConstraintInfoに対してを本関数をコールする。※含意またはIFが子に存在する場合に対応するため
/// @param[in] allocatable : 調停中のアロケータブル
/// @param[out] targets : 再調停対象アロケータブル
/// @param[in] isNot : 否定演算子による正否の逆転状態
void RBAConstraintInfo::collectRearbitrationTargetFor(
    const RBAAllocatable* const allocatable, std::set<const RBAAllocatable*>& targets,
    const bool isNot) const
{
  if (isExceptionBeforeArbitrate()) {
    return;
  }
  if (children_.empty() == false) {
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        if (children_.front()->isTrue()) {
          if (isNot) {
            children_.back()->collectTrueAllocatables(targets);
          } else {
            children_.back()->collectFalseAllocatables(targets);
          }
        } else if (!children_.front()->isFalse()) {
          children_.back()->collectRearbitrationTargetFor(allocatable, targets,
                                                          isNot);
        } else {
        }
        break;
      case RBAModelElementType::IfStatement:
        if (isNot) {
          children_.back()->collectTrueAllocatables(targets);
        } else {
          children_.back()->collectFalseAllocatables(targets);
        }
        break;
      case RBAModelElementType::NotOperator:
        // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
        // 【ルールに逸脱している内容】
        // Function '::rba::RBAConstraintInfo::collectRearbitrationTargetFor=(_,p={c::rba::RBAAllocatable},
        // &{c::std::set<p={c::rba::RBAAllocatable},{c::std::less<p={c::rba::RBAAllocatable}>},
        // {c::std::allocator<p={c::rba::RBAAllocatable}>}>},_o)' is recursive. 
        // 【ルールを逸脱しても問題ないことの説明】
        // 機能として再帰呼び出しが必要なため
        children_.front()->collectRearbitrationTargetFor(allocatable, targets,
                                                         !isNot);
        break;
      default:
        for (const auto& child : children_) {
          child->collectRearbitrationTargetFor(allocatable, targets, isNot);
        }
        break;
    }
  }
}

void RBAConstraintInfo::collectTrueAllocatables(
    std::set<const RBAAllocatable*>& allocatables) const
{
  if (isExceptionBeforeArbitrate() || isFalse()) {
    return;
  }
  if (isRevert()) {
    for (const auto& child : children_) {
      child->collectFalseAllocatables(allocatables);
    }
    allocatables.insert(falseAllocatables_.begin(), falseAllocatables_.end());
  } else if (isImplies()) {
    children_.back()->collectTrueAllocatables(allocatables);
  } else if (isSizeOperator()) {
    // サイズオペレーターは集合の数を評価するので、FalseAllocatableとTrueAllocatableを合わせたAllocatableがTrueAllocatablesとなる
    children_.back()->collectTrueAllocatables(allocatables);
    children_.back()->collectFalseAllocatables(allocatables);
  } else {
    for (const auto& child : children_) {
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      // 【ルールに逸脱している内容】
      // Function '::rba::RBAConstraintInfo::collectTrueAllocatables=(_,&{c::std::set<p={c::rba::RBAAllocatable},
      // {c::std::less<p={c::rba::RBAAllocatable}>},{c::std::allocator<p={c::rba::RBAAllocatable}>}>})' is recursive. 
      // 【ルールを逸脱しても問題ないことの説明】
      // 機能として再帰呼び出しが必要なため
      child->collectTrueAllocatables(allocatables);
    }
    allocatables.insert(trueAllocatables_.begin(), trueAllocatables_.end());
  }
  return;
}

void RBAConstraintInfo::collectFalseAllocatables(
    std::set<const RBAAllocatable*>& allocatables) const
{
  if (isExceptionBeforeArbitrate() || isTrue()) {
    return;
  }
  if (isRevert()) {
    for (const auto& child : children_) {
      child->collectTrueAllocatables(allocatables);
    }
    allocatables.insert(trueAllocatables_.begin(), trueAllocatables_.end());
  } else if (isImplies()) {
    children_.back()->collectFalseAllocatables(allocatables);
  } else if (isSizeOperator()) {
    // サイズオペレーターは集合の数を評価するので、FalseAllocatableとTrueAllocatableを合わせたAllocatableがFalseAllocatablesとなる
    children_.back()->collectTrueAllocatables(allocatables);
    children_.back()->collectFalseAllocatables(allocatables);
  } else {
    for (const auto& child : children_) {
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      // 【ルールに逸脱している内容】
      // Function '::rba::RBAConstraintInfo::collectFalseAllocatables=(_,&{c::std::set<p={c::rba::RBAAllocatable},
      // {c::std::less<p={c::rba::RBAAllocatable}>},{c::std::allocator<p={c::rba::RBAAllocatable}>}>})' is recursive. 
      // 【ルールを逸脱しても問題ないことの説明】
      // 機能として再帰呼び出しが必要なため
      child->collectFalseAllocatables(allocatables);
    }
    allocatables.insert(falseAllocatables_.begin(), falseAllocatables_.end());
  }
  return;
}

bool RBAConstraintInfo::contains(const RBAAllocatable* const allocatable) const
{
  if (allocatable != nullptr) {
    if (trueAllocatables_.find(allocatable) != trueAllocatables_.end()) {
      return true;
    }
    if (falseAllocatables_.find(allocatable) != falseAllocatables_.end()) {
      return true;
    }
  } else {
    if (!trueAllocatables_.empty() || !falseAllocatables_.empty()) {
      return true;
    }
  }
  for (const auto& child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // 【ルールに逸脱している内容】
    // Function '::rba::RBAConstraintInfo::contains=(_,p={c::rba::RBAAllocatable})' is recursive. 
    // 【ルールを逸脱しても問題ないことの説明】
    // 機能として再帰呼び出しが必要なため
    if (child->contains(allocatable)) {
      return true;
    }
  }
  return false;
}

bool RBAConstraintInfo::isTrue() const
{
  return (result_ == RBAExecuteResult::TRUE);
}

bool RBAConstraintInfo::isFalse() const
{
  return (result_ == RBAExecuteResult::FALSE);
}

void RBAConstraintInfo::collectAffectedAllocatables(
    const bool isRevert, std::set<const RBAAllocatable*>& affectAllocatables,
    const bool collecting,
    const bool forObject)
{
  // 制約式をFalseにした原因アロケータブルを収集する
  // 制約式評価時に作成したツリー構造のConstraintInfoを
  // 本関数で再帰呼び出しすることで実装している。
  // 否定より下のConstraintInfoは成否が反転するためTrueを収集するようにしている
  switch (getExpression()->getModelElementType()) {
    case RBAModelElementType::NotOperator:
      // 否定より下のConstraintInfoは成否が反転するためisRevertを反転させて、子Infoを呼び出す
      children_[0U]->collectAffectedAllocatables(!isRevert, affectAllocatables,
                                                 collecting, forObject);
      break;
    case RBAModelElementType::SizeOperator:
      // サイズオペレーターは集合の数を評価するので、FalseAllocatableとTrueAllocatableを合わせたAllocatableがaffectAllocatablesとなる
      children_[0U]->collectAffectedAllocatables(false, affectAllocatables,
                                                 true, true);
      break;
    case RBAModelElementType::OrOperator:
    case RBAModelElementType::ExistsOperator:
      // "Exists {A,B}{x|x.isXXX}"は"A.isXXX OR B.isXXX"と等価であるため、同一処理を行う
      if (!isRevert) {
        // 奇数個の否定で修飾されていない、評価結果がFalseまたはSkipの、ORのInfoに来た時の処理
        if (!isTrue()) {
          // 評価結果がFalseの子Infoのアロケータブルを収集する
          // A.isXXX OR B.isXXX のとき、Aの評価結果がTrueであれば、Bの評価結果がFalseでも、
          // ORの評価結果がTrueになる。よって、AはBに影響を与えている。逆にBもAに影響を与えている
          // よって、collectingをTrueにして子Infoに影響アロケータブルを探しにいく。
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables, true,
                                           forObject);  //ORの時に収集する
          }
        }
      } else {
        // 奇数個の否定で修飾されている、評価結果がTrueまたはSkipの、ORのInfoに来た時の処理
        // "!(A.isXXX OR B.isXXX)"は"!A.isXXX AND !B.isXXX"に分解できるため、
        // NOTの場合はANDと同じ処理を行う
        if (!isFalse()) {
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables,
                                           collecting, forObject);
          }
        }
      }
      break;
    case RBAModelElementType::AndOperator:
    case RBAModelElementType::ForAllOperator:
      // "For-All {A,B}{x|x.isXXX}"は"A.isXXX AND B.isXXX"と等価であるため、同一処理を行う
      if (isRevert) {
        // 奇数個の否定で修飾されている、評価結果がTrueまたはSkipの、ANDのInfoに来た時の処理
        // "!(A.isXXX AND B.isXXX)"は"!A.isXXX OR !B.isXXX"に分解できるため、
        // NOTの場合はORと同じ処理を行う
        if (!isFalse()) {
          for (auto& i : children_) {
            // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
            // 【ルールに逸脱している内容】
            // Function '::rba::RBAConstraintInfo::collectAffectedAllocatables(_,_o,&{c::std::set<p={c::rba::RBAAllocatable},
            // {c::std::less<p={c::rba::RBAAllocatable}>},{c::std::allocator<p={c::rba::RBAAllocatable}>}>},_o)' is recursive.
            // 【ルールを逸脱しても問題ないことの説明】
            //  機能として再帰呼び出しが必要なため
            i->collectAffectedAllocatables(isRevert, affectAllocatables, true,
                                           forObject);
          }
        }
      } else {
        // 奇数個の否定で修飾されてない、評価結果がFalseまたはSkipの、ANDのInfoに来た時の処理
        // A.isXXX AND B.isXXX のとき、Aの評価結果が何であろうと、Bの評価結果がTrueにならなければ、
        // ANDの評価結果がTrueにならないので、AはBに影響を与えない。また、BもAに影響を与えない。
        // よって、collectingはそのままで子Infoに影響アロケータブルを探しにいく。
        if (!isTrue()) {
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables,
                                           collecting, forObject);
          }
        }
      }
      break;
    case RBAModelElementType::MaxOperator:
    case RBAModelElementType::MinOperator:
    {
      // <集合>式がIF(A.isDisplayed) THEN {B,C} ELSE {D,E}のとき、影響エリアとしてAを抽出するために左辺を走査する
      children_[0U]->collectAffectedAllocatables(false, affectAllocatables,
                                                 collecting,forObject);
      // ラムダ式の x となった全てのオペランドがお互いに影響を与えているので、影響エリアとして抽出する必要がある
      for (std::uint8_t i { 1U }; i < children_.size(); ++i) {
        children_[i]->collectAffectedAllocatables(isRevert, affectAllocatables,
                                                  true, true);
      }
      break;
    }
    case RBAModelElementType::ImpliesOperator:  // A -> B は !A OR Bと同じ
      if (!isRevert) {
        if (!isTrue()) {
          // "A.isXXX -> B.isXXX"は"!A.isXXX OR B.isXXX"に分解できるため、ORと同じ処理を行う
          // 上記理由により、左辺の取得対象はisRevertを反転させる。
          children_[0U]->collectAffectedAllocatables(!isRevert,
                                                     affectAllocatables, true,
                                                     forObject);
          children_[1U]->collectAffectedAllocatables(isRevert,
                                                     affectAllocatables, true,
                                                     forObject);
        }
      } else {
        if (!isFalse()) {
          // "!(A.isXXX -> B.isXXX)"は"A.isXXX OR !B.isXXX"に分解できるため、ORと同じ処理を行う
          // 上記理由により、左辺の取得対象はisRevertを反転させる。
          children_[0U]->collectAffectedAllocatables(!isRevert,
                                                     affectAllocatables,
                                                     collecting, forObject);
          children_[1U]->collectAffectedAllocatables(isRevert,
                                                     affectAllocatables,
                                                     collecting, forObject);
        }
      }
      break;
    case RBAModelElementType::IfStatement:  // IF(A) THEN B ELSE C は AがTrueなら !A OR B、Falseなら A OR Cと同じ
      if (children_[0U]->isTrue()) {
        if (!isRevert) {
          if (!isTrue()) {
            // "IF(A.isXXX) THEN B.isXXX ELSE C.isXXX"はAがTrueのとき、"(!A.isXXX OR B.isXXX)"に分解できる
            // 上記理由により、左辺の取得対象はisRevertを反転させる。
            children_[0U]->collectAffectedAllocatables(!isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        } else {
          if (!isFalse()) {
            // "!(IF(A.isXXX) THEN B.isXXX ELSE C.isXXX)"はAがTrueのとき、"(!A.isXXX OR !B.isXXX)"に分解できる
            // 上記理由により、左辺の取得対象はisRevertを反転させる。
            children_[0U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        }
      } else {
        if (!isRevert) {
          if (!isTrue()) {
            // "IF(A.isXXX) THEN B.isXXX ELSE C.isXXX"はAがFalseのとき、"(A.isXXX OR C.isXXX)"に分解できる
            children_[0U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        } else {
          if (!isFalse()) {
            // "!(IF(A.isXXX) THEN B.isXXX ELSE C.isXXX)"はAがFalseのとき、"(A.isXXX OR !C.isXXX)"に分解できる
            children_[0U]->collectAffectedAllocatables(!isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        }
      }
      break;
    default:  //Allocatableを収集
      if (collecting) {
        if (isRevert) {
          affectAllocatables.insert(trueAllocatables_.begin(),
                                    trueAllocatables_.end());
        } else {
          affectAllocatables.insert(falseAllocatables_.begin(),
                                    falseAllocatables_.end());
        }
        if (forObject) {
          for (const auto& a : operandAllocatable_) {
            affectAllocatables.insert(a);
          }
        }
      }
      for (auto& i : children_) {
        i->collectAffectedAllocatables(isRevert, affectAllocatables, collecting,
                                       forObject);
      }
      break;
  }
  return;
}

}


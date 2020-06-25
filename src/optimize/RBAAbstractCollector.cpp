/**
 * 抽象探索クラス実装ファイル
 */

#include <memory>

#include "RBAAbstractCollector.hpp"

#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAAllocatedContent.hpp"
#include "RBAAndOperator.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAContentValue.hpp"
#include "RBADisplayingContent.hpp"
#include "RBAExistsOperator.hpp"
#include "RBAForAllOperator.hpp"
#include "RBAGetAllocatables.hpp"
#include "RBAActiveState.hpp"
#include "RBAActiveContents.hpp"
#include "RBAGetContentsList.hpp"
#include "RBAGetProperty.hpp"
#include "RBAHasBeenDisplayed.hpp"
#include "RBAHasComeEarlierThan.hpp"
#include "RBAHasComeLaterThan.hpp"
#include "RBAIfStatement.hpp"
#include "RBAImpliesOperator.hpp"
#include "RBAIsActive.hpp"
#include "RBAIsAttenuated.hpp"
#include "RBAIsDisplayed.hpp"
#include "RBAIsEqualToOperator.hpp"
#include "RBAIsGreaterThanEqualOperator.hpp"
#include "RBAIsGreaterThanOperator.hpp"
#include "RBAIsHidden.hpp"
#include "RBAIsLowerThanEqualOperator.hpp"
#include "RBAIsLowerThanOperator.hpp"
#include "RBAIsMuted.hpp"
#include "RBAIsOn.hpp"
#include "RBAIsOutputted.hpp"
#include "RBAIsSounding.hpp"
#include "RBAIsVisible.hpp"
#include "RBALambdaExpression.hpp"
#include "RBAModelImpl.hpp"
#include "RBANotOperator.hpp"
#include "RBAObjectCompare.hpp"
#include "RBAOrOperator.hpp"
#include "RBAOutputtingSound.hpp"
#include "RBAPreviousModifier.hpp"
#include "RBAMaxOperator.hpp"
#include "RBAMinOperator.hpp"
#include "RBASelectOperator.hpp"
#include "RBASizeOperator.hpp"
#include "RBAResultImpl.hpp"
#include "RBAResultSet.hpp"
#include "RBAStateValue.hpp"
#include "RBAObjectReference.hpp"
#include "RBASetOfOperator.hpp"
#include "RBALetStatement.hpp"
#include "RBAOperator.hpp"
#include "RBAIsTypeOfOperator.hpp"
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

RBAAbstractCollector::RBAAbstractCollector(RBAModelImpl* const model)
    : RBAExpressionVisitor(),
      model_{model},
      isLhs_{false},
      isPreviousModifier_{false},
      isPositive_{true},
      visitsLetStatement_{false}
{
}

// エリアの状態参照
void RBAAbstractCollector::visit(RBAIsDisplayed& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBADisplayingContent& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAAllocatedContent& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsHidden& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAContentValue& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetContentsList& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

void RBAAbstractCollector::visit(RBAActiveContents& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

// 表示コンテントの状態参照
void RBAAbstractCollector::visit(RBAIsActive& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsVisible& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAStateValue& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasBeenDisplayed& exp)
{
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasComeEarlierThan& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasComeLaterThan& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetAllocatables& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAActiveState& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// ゾーンの状態参照
void RBAAbstractCollector::visit(RBAIsOutputted& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAOutputtingSound& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// allocatedContentはエリアと共通
void RBAAbstractCollector::visit(RBAIsMuted& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsAttenuated& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// contentValueはエリアと共通
// contentsListはエリアと共通

// 音声コンテントの状態参照
// isActiveは表示コンテントと共通
void RBAAbstractCollector::visit(RBAIsSounding& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// stateValueは表示コンテントと共通
// hasComeEarlierThanは表示コンテントと共通
// hasComeLaterThanは表示コンテントと共通
// allocatablesは表示コンテントと共通

// シーン参照
void RBAAbstractCollector::visit(RBAIsOn& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetProperty& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

void RBAAbstractCollector::visit(RBAIsTypeOfOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

// 演算子
void RBAAbstractCollector::visit(RBAAndOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visit(RBAOrOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visit(RBANotOperator& exp)
{
  visitLetStatement(exp);
  isPositive_ = !isPositive_;
  exp.getLhsOperand()->accept(*this);
  isPositive_ = !isPositive_;
}
void RBAAbstractCollector::visit(RBAImpliesOperator& exp)
{
  visitLetStatement(exp);
  const bool backup {isLhs_};
  exp.getLhsOperand()->accept(*this);
  isLhs_ = backup;
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsEqualToOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAObjectCompare& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsGreaterThanOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsGreaterThanEqualOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsLowerThanOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsLowerThanEqualOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}

// 量化記号
void RBAAbstractCollector::visit(RBAForAllOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitrator dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // このパスを通るとき、LetStatementのValiableを参照している可能性がある
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBAExistsOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitrator dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // このパスを通るとき、LetStatementのValiableを参照している可能性がある
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}

// 組込み定義式
void RBAAbstractCollector::visit(RBAAllInstanceOfArea& exp)
{
  // このVisitorの実装は、ForAllとExistsの集合をReferenceObjectで参照し、
  // それをValiableに設定後、bodyへacceptする挙動となっており、
  // 集合にはacceptしないので、このパスを通ることはない
}
void RBAAbstractCollector::visit(RBAAllInstanceOfViewContent& exp)
{
  // このVisitorの実装は、ForAllとExistsの集合をReferenceObjectで参照し、
  // それをValiableに設定後、bodyへacceptする挙動となっており、
  // 集合にはacceptしないので、このパスを通ることはない
}
void RBAAbstractCollector::visit(RBAAllInstanceOfZone& exp)
{
  // このVisitorの実装は、ForAllとExistsの集合をReferenceObjectで参照し、
  // それをValiableに設定後、bodyへacceptする挙動となっており、
  // 集合にはacceptしないので、このパスを通ることはない
}
void RBAAbstractCollector::visit(RBAAllInstanceOfSoundContent& exp)
{
  // このVisitorの実装は、ForAllとExistsの集合をReferenceObjectで参照し、
  // それをValiableに設定後、bodyへacceptする挙動となっており、
  // 集合にはacceptしないので、このパスを通ることはない
}

// 構文
void RBAAbstractCollector::visit(RBAIfStatement& exp)
{
  visitLetStatement(exp);
  const bool backup {isLhs_};
  isLhs_ = true;
  exp.getCondition()->accept(*this);
  isLhs_ = backup;
  exp.getThenExpression()->accept(*this);
  exp.getElseExpression()->accept(*this);
}
void RBAAbstractCollector::visit(RBALetStatement& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// 修飾子
void RBAAbstractCollector::visit(RBAPreviousModifier& exp)
{
  visitLetStatement(exp);
  const bool b_isPreviousModifier_ {isPreviousModifier_};
  isPreviousModifier_ = true;
  exp.getObjReference()->accept(*this);
  isPreviousModifier_ = b_isPreviousModifier_;
}
// 集合操作
void RBAAbstractCollector::visit(RBAMaxOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitrator dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // このパスを通るとき、LetStatementのValiableを参照している可能性がある
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBAMinOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitrator dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // このパスを通るとき、LetStatementのValiableを参照している可能性がある
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBASelectOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitrator dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // このパスを通るとき、LetStatementのValiableを参照している可能性がある
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBASizeOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// オブジェクトリファレンス
void RBAAbstractCollector::visit(RBAObjectReference& exp)
{
  visitLetStatement(exp);
}
void RBAAbstractCollector::visit(RBASetOfOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visitLetStatement(RBAExpression& exp)
{
  const bool backup_let {visitsLetStatement_};
  visitsLetStatement_ = true;
  for (auto& letStatement : exp.getLetStatements()) {
    letStatement->accept(*this);
  }
  visitsLetStatement_ = backup_let;
}

std::set<const RBARuleObject*>& RBAAbstractCollector::getLetVal()
{
  return letVal_;
}

void RBAAbstractCollector::addLetVal(const RBARuleObject* const obj)
{
  static_cast<void>(letVal_.insert(obj));
}

bool RBAAbstractCollector::isVisitsLetStatement() const
{
  return visitsLetStatement_;
}

bool RBAAbstractCollector::isLhs() const
{
  return isLhs_;
}

void RBAAbstractCollector::setLhs(const bool lhs)
{
  isLhs_ = lhs;
}

bool RBAAbstractCollector::isPositive() const
{
  return isPositive_;
}

RBAModelImpl* RBAAbstractCollector::getModel() const
{
  return model_;
}

bool RBAAbstractCollector::isPreviousModifier() const 
{
  return isPreviousModifier_;
}




} /* namespace rba */

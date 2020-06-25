/**
 * オブジェクト比較クラス定義ファイル
 */

#include "RBAObjectCompare.hpp"
#include "RBAAllocatable.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void
RBAObjectCompare::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAObjectCompare::getModelElementType() const
{
  return RBAModelElementType::ObjectCompare;
}

bool
RBAObjectCompare::executeCore(RBAConstraintInfo* info,
                              RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBAExpression* const lhs {getLhsOperand()};
  // カバレッジ向けの制約階層構造に左辺を追加 
  LOG_addHierarchy("#left");
  const RBARuleObject* const lhobj {lhs->getReferenceObject(leftInfo, arb)};
  // カバレッジ向けの制約階層構造から左辺を削除
  LOG_removeHierarchy();
  // 参照で調停前例外が片方でも出た場合は上位にスロー
  if (leftInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    RBAConstraintInfo* const rightInfo {info->getChild(1U)};
    const RBAExpression* const rhs {getRhsOperand()};
    // カバレッジ向けの制約階層構造に右辺を追加
    LOG_addHierarchy("#right");
    const RBARuleObject* const rhobj {rhs->getReferenceObject(rightInfo, arb)};
    // カバレッジ向けの制約階層構造から右辺を削除
    LOG_removeHierarchy();
    // 参照で調停前例外が片方でも出た場合は上位にスロー
    if (rightInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    } else {
      // オブジェクトが2つ取り出せなければfalse
      if ((lhobj != nullptr) && (rhobj != nullptr)) {
        if (lhobj->getRawObject() == rhobj->getRawObject()) {
          isPassed = true;
          // ObjectRefrenceをオペランドとするObjectCompareは再調停により、評価結果がfalseからTrueになることが無いので、
          // 再調停のためのFalseAllocatableやTrueAllocatabeの追加は必要ない
          // AllocatedContentなどのExpressionをオペランドとする場合には、
          // オペランドにて、FalseAllocatableやTrueAllocatabeの追加するため、ObjectCompareでは追加する必要がない。
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] true");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  }
#endif
  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAObjectCompare::getSymbol() const
{
  return "==";
}

const std::string
RBAObjectCompare::getExpressionText() const
{
  return getLhsOperand()->getExpressionText()
    + " " + getSymbol() + " " + getRhsOperand()->getExpressionText();
}

const std::string
RBAObjectCompare::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText()
    + " " + getSymbol() + " " + getRhsOperand()->getCoverageExpressionText();
}

void
RBAObjectCompare::createHierarchy()
{
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  RBAExpression*  expr0 = getLhsOperand();
  RBAExpression*  expr1 = getRhsOperand();

  // カバレッジ向けの制約階層構造に左辺を追加
  LOG_addHierarchy("#left");
  expr0->createHierarchy();
  // カバレッジ向けの制約階層構造から左辺を削除
  LOG_removeHierarchy();

  // カバレッジ向けの制約階層構造に右辺を追加
  LOG_addHierarchy("#right");
  expr1->createHierarchy();
  // カバレッジ向けの制約階層構造から右辺を削除
  LOG_removeHierarchy();

  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
}

RBAExpressionType
RBAObjectCompare::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

/**
 * 含意オペレータクラス定義ファイル
 */

#include "RBAImpliesOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAImpliesOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAImpliesOperator::getModelElementType() const
{
  return RBAModelElementType::ImpliesOperator;
}

bool
RBAImpliesOperator::executeCore(RBAConstraintInfo* info,
                                RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());  // カバレッジ向けの制約階層構造に自分を追加
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  LOG_addHierarchy("#left");  // カバレッジ向けの制約階層構造に左辺を追加
  const bool lhsRes {getLhsOperand()->execute(leftInfo, arb)};
  LOG_removeHierarchy();  // カバレッジ向けの制約階層構造から左辺を削除

  if (leftInfo->isExceptionBeforeArbitrate() == false) {
    if (lhsRes == false) {
      isPassed = true;
    } else {
      RBAConstraintInfo* const rightInfo {info->getChild(1U)};
      LOG_addHierarchy("#right");  // カバレッジ向けの制約階層構造に右辺を追加
      const bool rhsRes {getRhsOperand()->execute(rightInfo, arb)};
      LOG_removeHierarchy();  // カバレッジ向けの制約階層構造から右辺を削除
      if (rightInfo->isExceptionBeforeArbitrate() == true) {
        info->setExceptionBeforeArbitrate(true);
      } else if (rhsRes == true) {
        isPassed = true;
      } else {
        ;
      }
    }
  } else {
    info->setExceptionBeforeArbitrate(true);
    // 右辺の再調停対象アロケータブルを取得するために、右辺の評価を実行する
    RBAConstraintInfo* const rightInfo {info->getChild(1U)};
    LOG_addHierarchy("#right");  // カバレッジ向けの制約階層構造に右辺を追加
    static_cast<void>(getRhsOperand()->execute(rightInfo, arb));
    LOG_removeHierarchy();  // カバレッジ向けの制約階層構造から右辺を削除
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate()) {
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
  LOG_removeHierarchy();  // カバレッジ向けの制約階層構造から自分を削除
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAImpliesOperator::getSymbol() const
{
  return "->";
}

void
RBAImpliesOperator::createHierarchy()
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();

  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  // カバレッジ向けの制約階層構造に左辺を追加
  LOG_addHierarchy("#left");
  exprLhs->createHierarchy();
  // カバレッジ向けの制約階層構造から左辺を削除
  LOG_removeHierarchy();

  // カバレッジ向けの制約階層構造に右辺を追加
  LOG_addHierarchy("#right");
  exprRhs->createHierarchy();
  // カバレッジ向けの制約階層構造から右辺を削除
  LOG_removeHierarchy();

  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
}
#endif

}

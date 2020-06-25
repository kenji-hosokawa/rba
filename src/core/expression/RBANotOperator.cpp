/**
 * NOTオペレータクラス定義ファイル
 */

#include "RBANotOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBANotOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBANotOperator::getModelElementType() const
{
  return RBAModelElementType::NotOperator;
}

bool
RBANotOperator::executeCore(RBAConstraintInfo* info,
                            RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());  // カバレッジ向けの制約階層構造に自分を追加
  RBAConstraintInfo* const childInfo {info->getChild(0U)};
  const bool isChildPassed {getLhsOperand()->execute(childInfo, arb)};
  if (childInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    isPassed = !isChildPassed;
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
  LOG_removeHierarchy();  // カバレッジ向けの制約階層構造から自分を削除
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBANotOperator::getSymbol() const
{
  return "!";
}

const std::string
RBANotOperator::getExpressionText() const
{
  return getSymbol() + getLhsOperand()->getExpressionText();
}

const std::string
RBANotOperator::getCoverageExpressionText() const
{
  return getSymbol() + getLhsOperand()->getCoverageExpressionText();
}
#endif

}

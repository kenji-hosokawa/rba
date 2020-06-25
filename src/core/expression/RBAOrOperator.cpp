/**
 * ORオペレータクラス定義ファイル
 */

#include "RBAOrOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAOrOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAOrOperator::getModelElementType() const
{
  return RBAModelElementType::OrOperator;
}

bool
RBAOrOperator::executeCore(RBAConstraintInfo* info,
                           RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  std::uint32_t index {0U};
  for (const RBAExpression* const ope : getOperand()) {
    RBAConstraintInfo* const childInfo {info->getChild(index)};
    // カバレッジ向けの制約階層構造に回数を追加
    LOG_addHierarchy("#" + std::to_string(index));
    const bool res {ope->execute(childInfo, arb)};
    // カバレッジ向けの制約階層構造から回数を削除
    LOG_removeHierarchy();
    if (childInfo->isExceptionBeforeArbitrate() == true) {
      info->setExceptionBeforeArbitrate(true);
    } else if (res == true) {
      isPassed = true;
    } else {
      ;
    }
    ++index;
  }
  if (isPassed == true) {
    info->setExceptionBeforeArbitrate(false);
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
RBAOrOperator::getSymbol() const
{
  return "OR";
}
#endif

}

/// 大なりチェックオペレータクラス定義ファイル

#include "RBAIsGreaterThanOperator.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAModelElementType
RBAIsGreaterThanOperator::getModelElementType() const
{
  return RBAModelElementType::IsGreaterThanOperator;
}

void
RBAIsGreaterThanOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

bool
RBAIsGreaterThanOperator::executeCore(RBAConstraintInfo* info,
                                      RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  const std::int32_t lhsVal {getLhsOperand()->getValue(leftInfo, arb)};
  const std::int32_t rhsVal {getRhsOperand()->getValue(rightInfo, arb)};
  // 参照で調停前例外が片方でも出た場合は上位にスロー
  if ((leftInfo->isExceptionBeforeArbitrate() == true)
      || (rightInfo->isExceptionBeforeArbitrate() == true)
      || (lhsVal == -99)
      || (rhsVal == -99)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (lhsVal > rhsVal) {
      isPassed = true;
      info->addTrueAllocatableFromOperand();
    } else {
      info->addFalseAllocatableFromOperand();
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
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsGreaterThanOperator::getSymbol() const
{
  return ">";
}

RBAExpressionType
RBAIsGreaterThanOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

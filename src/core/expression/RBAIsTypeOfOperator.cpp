//
// IsTypeOfクラスヘッダファイル
//

#include "RBAIsTypeOfOperator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBALogManager.hpp"
#include "RBARuleObject.hpp"

namespace rba
{

void RBAIsTypeOfOperator::setTag(const std::string& tag)
{
  tagId_ = tag;
}

void RBAIsTypeOfOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}
RBAModelElementType RBAIsTypeOfOperator::getModelElementType() const
{
  return RBAModelElementType::IsTypeOfOperator;
}
bool RBAIsTypeOfOperator::executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo * const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if (leftInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    isPassed = ruleObj->containsTag(tagId_);
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate()) {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getExpressionText() + " before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if ((ruleObj == nullptr) || (!isPassed)) {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getExpressionText() + " false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getExpressionText() + " true");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  }
#endif
  LOG_removeHierarchy();
  return isPassed;
}
#ifdef RBA_USE_LOG
const std::string RBAIsTypeOfOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string RBAIsTypeOfOperator::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}

const std::string RBAIsTypeOfOperator::getSymbol() const
{
  return ".isTypeOf(" + tagId_ + ")";
}

RBAExpressionType RBAIsTypeOfOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif
}
/* namespace rba */

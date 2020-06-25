//
// .hasBeenDisplayed()のヘッダーファイル
//

#include "RBAHasBeenDisplayed.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void RBAHasBeenDisplayed::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType RBAHasBeenDisplayed::getModelElementType() const
{
  return RBAModelElementType::HasBeenDisplayed;
}

bool RBAHasBeenDisplayed::executeCore(RBAConstraintInfo* info,
                                      RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    const RBAContent* const c {
        dynamic_cast<const RBAContent*>(ruleObj->getRawObject())};
    if (!ruleObj->isPrevious()) {
      isPassed = arb->getResult()->hasBeenDisplayed(c);
    } else {
      isPassed = arb->getResult()->hasBeenPreDisplayed(c);
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  RBAExecuteResult r;
  std::string cname;
  std::string resultStr;
  if (ruleObj != nullptr) {
    cname = ruleObj->getRawObject()->getElementName();
  } else {
    cname = "NULL";
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultStr = " before arbitrate skip";
    r = RBAExecuteResult::SKIP;
  } else if (isPassed) {
    resultStr = " true";
    r = RBAExecuteResult::TRUE;
  } else {
    resultStr = " false";
    r = RBAExecuteResult::FALSE;
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      Content[" + cname + "]" + getSymbol() + resultStr);
  LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(), r);
#endif
  LOG_removeHierarchy();
  return isPassed;
}

// Log
#ifdef RBA_USE_LOG
const std::string RBAHasBeenDisplayed::getSymbol() const
{
  return ".hasBeenDisplayed()";
}
RBAExpressionType RBAHasBeenDisplayed::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif
} /* namespace rba */

//
// activeState定義ファイル
//

#include "RBAActiveState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAArbitrator.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void RBAActiveState::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}
RBAModelElementType RBAActiveState::getModelElementType() const
{
  return RBAModelElementType::ActiveState;
}
const RBARuleObject* RBAActiveState::getReferenceObjectCore(
    RBAConstraintInfo* info, RBAArbitrator* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    const RBAContent* const c {
        dynamic_cast<const RBAContent*>(ruleObj->getRawObject())};
    if (ruleObj->isPrevious()) {
      returnObj = arb->getResult()->getPreActiveState(c);
    } else {
      returnObj = arb->getResult()->getActiveState(c);
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  std::string str;
  if (info->isExceptionBeforeArbitrate()) {
    str = " is before arbitrate skip";
  } else if (ruleObj == nullptr) {
    str = " no Content";
  } else if (returnObj == nullptr) {
    str = " has no Active State";
  } else {
    str = " is " + returnObj->getElementName();
  }
  LOG_arbitrateConstraintLogicLogLine("      " + getExpressionText() + str);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string RBAActiveState::getSymbol() const
{
  return ".activeState()";
}
#endif
} /* namespace rba */

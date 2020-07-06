
/**
 * Allocated Content class
 */

#include "RBAAllocatedContent.hpp"

#include "RBAAllocatable.hpp"
#include "RBAArbitrator.hpp"
#include "RBAContentState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAAllocatedContent::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector which is the only visitor at the moment
  // does not accept this content, so it will not pass this path.
  //  
  // However, in the future, another visitor may accept it, so leave this.
  visitor.visit(*this);
}

RBAModelElementType
RBAAllocatedContent::getModelElementType() const
{
  return RBAModelElementType::AllocatedContent;
}

const RBARuleObject*
RBAAllocatedContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                            RBAArbitrator* arb) const
{
  const RBARuleObject* object {nullptr};  // return value
  const auto leftInfo = info->getChild(0U);
  const auto ruleObj = getLhsOperand()->getReferenceObject(leftInfo, arb);
  if (ruleObj != nullptr) {
    if (!leftInfo->isExceptionBeforeArbitrate()) {
      const RBAAllocatable* const alloc {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
      if (ruleObj->isPrevious() == true) {
        const auto contentState = arb->getResult()->getDirectPreContentState(alloc);
        if(contentState != nullptr) {
          object = contentState->getOwner();
        }
      } else if (alloc->isChecked()) {
        const auto contentState = alloc->getState();
        if (contentState != nullptr) {
          object = contentState->getOwner();
        }
        // At this point, it is unsure whether the constraint expression will be False or True,
        // so put it in both.
        info->addTrueAllocatable(alloc);
        info->addFalseAllocatable(alloc);
      } else {
        info->setExceptionBeforeArbitrate(true);
      }
    } else {
      info->setExceptionBeforeArbitrate(true);
    }
  }
#ifdef RBA_USE_LOG
  bool pre = false;
  std::string str;
  if (ruleObj == nullptr) {
    // Currently there is no constraint expression that returns an area. 
    // Therefore, ruleObj never becomes NULL.
    // In the future, a constraint expression that returns an area 
    // may be created, so leave this processing.
    str = "Allocatable[NULL] has no Content skip";
  } else {
    pre = ruleObj->isPrevious();
    if (info->isExceptionBeforeArbitrate()) {
      str = "Allocatable[" + ruleObj->getElementName() + "] is before arbitrate skip";
    } else if (object == nullptr) {
      str = "Allocatable[" + ruleObj->getElementName() + "] has no Allocated Content";
    } else {
      str = "Allocatable[" + ruleObj->getElementName() + "] has Allocated Content["
          + object->getElementName() + "]";
    }
  }
  LOG_arbitrateConstraintLogicLogLine("      " + getPreMsg(pre) + str);
#endif
  return object;
}

#ifdef RBA_USE_LOG
const std::string
RBAAllocatedContent::getSymbol() const
{
  return ".allocatedContent()";
}

void
RBAAllocatedContent::createHierarchy()
{
  getLhsOperand()->createHierarchy();
}
#endif

}

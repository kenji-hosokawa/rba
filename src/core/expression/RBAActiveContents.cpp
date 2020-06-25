//
// Selectオペレータ定義ファイル
//

#include <memory>
#include "RBAActiveContents.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAArbitrator.hpp"
#include "RBAAllocatable.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAActiveContents::RBAActiveContents()
: RBAAllocatableOperator(),
  contentSet_{std::make_unique<RBAContentSet>()}
{
}

void
RBAActiveContents::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAActiveContents::getModelElementType() const
{
  return RBAModelElementType::ActiveContents;
}

const RBARuleObject*
RBAActiveContents::getReferenceObjectCore(RBAConstraintInfo* info, RBAArbitrator* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const lhsObj {getLhsOperand()->getReferenceObject(leftInfo, arb)};

  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  }
  else if (lhsObj != nullptr) {
    contentSet_->clear();
    const RBAAllocatable* const alloc {dynamic_cast<const RBAAllocatable*>(lhsObj->getRawObject())};
#ifdef RBA_USE_LOG
    if (arb == nullptr) {
      // createHierarchy()からコールされるとき、このパスを通る
      returnObj = alloc->getContentSet();
    } else {
#endif
      for (auto& content : alloc->getInternalContents()) {
        if (alloc->isPrevious()) {
          if (arb->getResult()->isPreActive(content)) {
            contentSet_->addTarget(content);
          }
        } else {
          if (arb->getResult()->isActive(content)) {
            contentSet_->addTarget(content);
          }
        }
      }
      returnObj = contentSet_.get();
#ifdef RBA_USE_LOG
    }
#endif
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  std::string objName = "NULL";
  if (returnObj != nullptr) {
    objName = returnObj->getElementName();
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + LOG_getExpressionText() + " is " + objName);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string
RBAActiveContents::getSymbol() const
{
  return ".activeContents()";
}
#endif

}

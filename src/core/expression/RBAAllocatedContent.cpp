/**
 * AllocatedContentクラス
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
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテントにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
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
  const RBARuleObject* object {nullptr};  // 戻り値
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
        // この時点では制約式がFalseになるかTrueになるか不明なので、両方に入れておく
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
    // 現在エリアを返す制約式はない。よって、ruleObjがNULLになることはない。
    // 将来、エリアを返す制約式が作成されるかもしれないので、この処理を残しておく。
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

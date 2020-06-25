/**
 * ディスプレイングコンテントクラス定義ファイル
 */

#include "RBADisplayingContent.hpp"
#include "RBAAllocatable.hpp"
#include "RBAArbitrator.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAResultImpl.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void 
RBADisplayingContent::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテントにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBADisplayingContent::getModelElementType() const
{
  return RBAModelElementType::DisplayingContent;
}

const RBARuleObject*
RBADisplayingContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                             RBAArbitrator* arb) const
{
  const RBARuleObject* object {nullptr};  // 戻り値
  const auto leftInfo = info->getChild(0U);
  const auto ruleObj = getLhsOperand()->getReferenceObject(leftInfo, arb);
  if (!leftInfo->isExceptionBeforeArbitrate()) {
    if (ruleObj != nullptr) {
      const RBAAllocatable* const alloc {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
      if (ruleObj->isPrevious()) {
        if (!arb->getResult()->isPreHidden(alloc)) {
          const auto contentState = arb->getResult()->getDirectPreContentState(alloc);
          if (contentState != nullptr) {
            object = contentState->getOwner();
          }
        }
      } else {
        if (!alloc->isChecked()) {
          info->setExceptionBeforeArbitrate(true);
        }
        // Hidden判定未実施、または、Hidden判定済みでHiddenがfalseのとき、
        // allocatableに割り当たっているcontentStateを取得する
        else if (!alloc->isHiddenChecked() || !alloc->isHidden()) {
          const auto contentState = alloc->getState();
          if (contentState != nullptr) {
            object = contentState->getOwner();
          }
          // この時点では制約式がFalseになるかTrueになるか不明なので、両方に入れておく
          info->addFalseAllocatable(alloc);
          info->addTrueAllocatable(alloc);
        } else {
          ;
        }
      }
    }
  } else {
    info->setExceptionBeforeArbitrate(true);
  }
#ifdef RBA_USE_LOG
  bool pre = false;
  std::string operandName;
  std::string resultText;
  if (ruleObj == nullptr) {
    operandName = "NULL";
  } else {
    pre = ruleObj->isPrevious();
    operandName = ruleObj->getElementName();
  }
  if (leftInfo->isExceptionBeforeArbitrate()) {
    resultText = "is before arbitrate skip";
  } else if (object == nullptr) {
    if((ruleObj != nullptr) && dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())->isChecked()) {
      resultText = "has no Displayed Content";
    } else {
      resultText = "is before arbitrate skip";
    }
  } else {
    resultText = "has Displayed Content[" + object->getElementName() + "]";
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + getPreMsg(pre) + "Area[" + operandName + "] " + resultText);
#endif
  return object;
}

#ifdef RBA_USE_LOG
const std::string
RBADisplayingContent::getSymbol() const
{
  return ".displayingContent()";
}

void
RBADisplayingContent::createHierarchy()
{
  getLhsOperand()->createHierarchy();
}

RBAExpressionType
RBADisplayingContent::getUnderlyingType() const
{
  return RBAExpressionType::CONTENT;
}
#endif

}

/// オブジェクトリファレンスクラス定義ファイル

#include "RBAObjectReference.hpp"

#include "RBAExpressionVisitor.hpp"
#include "RBAVariable.hpp"
#include "RBAModelElementType.hpp"
#ifdef RBA_USE_LOG
#include "RBAAbstractProperty.hpp"
#include "RBASceneImpl.hpp"
#endif

namespace rba
{

void
RBAObjectReference::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAObjectReference::getModelElementType() const
{
  return RBAModelElementType::ObjectReference;
}

const RBARuleObject*
RBAObjectReference::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitrator* arb) const
{
  const RBARuleObject* obj {refObject_};
  if (obj->isModelElementType(RBAModelElementType::Variable)) {
    // 変数の場合はその参照
    const RBAVariable* const val {dynamic_cast<const RBAVariable*>(obj)};
    obj = val->getRuleObj();
    std::shared_ptr<RBAConstraintInfo> valInfo {val->getConstraintInfo()};
    if (valInfo != nullptr) {
      info->setChild(valInfo);
      if (valInfo->isExceptionBeforeArbitrate()) {
        info->setExceptionBeforeArbitrate(true);
      }
    }
  }
  return obj;
}

void
RBAObjectReference::setRefObject(const RBARuleObject* const newRefObject)
{
  refObject_ = newRefObject;
}

#ifdef RBA_USE_LOG

void
RBAObjectReference::setExpressionType(RBAExpressionType const newExprType)
{
  expressionType_ = newExprType;
}

void
RBAObjectReference::createHierarchy()
{
  // 構造に影響しないので何もしない
}

const std::string
RBAObjectReference::getExpressionText() const
{
  if (refObject_->isModelElementType(RBAModelElementType::Property)) {
    return dynamic_cast<const RBAAbstractProperty*>(refObject_)->getScene()->getElementName();
  }
  else if ((refObject_->isModelElementType(RBAModelElementType::ViewContentState)) ||
           (refObject_->isModelElementType(RBAModelElementType::SoundContentState))) {
    return (refObject_->getOwner()->getElementName() + "." + refObject_->getElementName());
  }
  if(refObject_->getElementName() != ""){
    return refObject_->getElementName();
  } else {
    return refObject_->getDynamicName();
  }
}

const std::string
RBAObjectReference::getCoverageExpressionText() const
{
  if (refObject_->isModelElementType(RBAModelElementType::Variable)) {
    const RBAVariable* var =
        dynamic_cast<const RBAVariable*>(refObject_);
    if (var->getRuleObj()) {
      if (var->getRuleObj()->getElementName() != "") {
        return var->getRuleObj()->getElementName();
      } else {
        return var->getRuleObj()->getDynamicName();
      }
    }
  }
  if ((refObject_->isModelElementType(RBAModelElementType::ViewContentState)) ||
      (refObject_->isModelElementType(RBAModelElementType::SoundContentState))) {
    return (refObject_->getOwner()->getElementName() + "." + refObject_->getElementName());
  }
  if(refObject_->getElementName() != ""){
    return refObject_->getElementName();
  } else {
    return refObject_->getDynamicName();
  }
}

RBAExpressionType
RBAObjectReference::getUnderlyingType() const
{
  return expressionType_;
}
#endif

}

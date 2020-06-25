/**
 * 調停前参照クラス定義ファイル
 */

#include "RBAPreviousModifier.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

RBAPreviousModifier::RBAPreviousModifier()
    : RBAExpression(),
      previousObj_{std::make_unique<RBAPreviousObjectWrapper>()}
{
}

void
RBAPreviousModifier::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // ルールオブジェクトにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

void
RBAPreviousModifier::setObjReference(RBAExpression* const newObjRef)
{
  objReference_ = newObjRef;
}

RBAExpression* const
RBAPreviousModifier::getObjReference() const
{
  return objReference_;
}

const RBARuleObject*
RBAPreviousModifier::getReferenceObjectCore(RBAConstraintInfo* info,
                                            RBAArbitrator* arb) const
{
  previousObj_->setRefObject(objReference_->getReferenceObject(info, arb));
  return previousObj_.get();
}

#ifdef RBA_USE_LOG
const std::string
RBAPreviousModifier::getSymbol() const
{
  return "(pre)";
}

void
RBAPreviousModifier::createHierarchy()
{
  objReference_->createHierarchy();
}

const std::string
RBAPreviousModifier::getExpressionText() const
{
  return getSymbol() + objReference_->getExpressionText();
}

const std::string
RBAPreviousModifier::getCoverageExpressionText() const
{
  return getSymbol() + objReference_->getCoverageExpressionText();
}

RBAExpressionType
RBAPreviousModifier::getUnderlyingType() const
{
  return objReference_->getUnderlyingType();
}

#endif

}

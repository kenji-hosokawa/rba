/**
 * プロパティ取得クラス定義ファイル
 */

#include "RBAGetProperty.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBASceneImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

void
RBAGetProperty::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテントにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAGetProperty::getModelElementType() const
{
  return RBAModelElementType::GetProperty;
}

std::int32_t
RBAGetProperty::getValueCore(RBAConstraintInfo* info,
				 RBAArbitrator* arb) const
{
  std::int32_t value{0};
  const RBAAbstractProperty* prop{nullptr};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(info, arb)};
  if(ruleObj->isPrevious()) {
    prop = dynamic_cast<const RBAAbstractProperty*>(ruleObj->getRawObject());
    value = arb->getResult()->getPreSceneProperty(prop);
  }
  else {
    prop = dynamic_cast<const RBAAbstractProperty*>(ruleObj);
    value = arb->getResult()->getSceneProperty(prop);
  }
  LOG_arbitrateConstraintLogicLogLine("      "
				      + getPreMsg(ruleObj->isPrevious())
				      + "Property["
				      + prop->getScene()->getElementName()
				      + "::"
				      + prop->getElementName()
				      + "] get["
				      + std::to_string(value)
				      + "]");
  return value;
}

#ifdef RBA_USE_LOG
const std::string
RBAGetProperty::getSymbol() const
{
  return ".get()";
}

const std::string
RBAGetProperty::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string
RBAGetProperty::getCoverageExpressionText() const
{
  return getExpressionText();
}

RBAExpressionType
RBAGetProperty::getUnderlyingType() const
{
  return RBAExpressionType::VALUE;
}
#endif

}

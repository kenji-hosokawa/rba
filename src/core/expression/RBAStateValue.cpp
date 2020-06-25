/// ステート値クラス定義ファイル

#include <string>
#include "RBAStateValue.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAStateValue::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // Valueを返すexpressionにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAStateValue::getModelElementType() const
{
  return RBAModelElementType::StateValue;
}

std::int32_t
RBAStateValue::getValueCore(RBAConstraintInfo* info, RBAArbitrator* arb) const
{
  std::int32_t result { -99 };
  const auto leftInfo = info->getChild(0U);
  const auto r = getLhsOperand()->getReferenceObject(leftInfo, arb);
  const RBAContent* c { nullptr };
  const RBAContentState* cs { nullptr };
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (r != nullptr) {
      c = dynamic_cast<const RBAContent*>(r->getRawObject());
      if (c != nullptr) {
        if (r->isPrevious()) {
          cs = arb->getResult()->getPreActiveState(c);
        } else {
          cs = arb->getResult()->getActiveState(c);
        }
        if (cs != nullptr) {
          result = cs->getContentStatePriority();
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string pre;
  std::string cName { "NULL" };
  std::string resultText{ "no Content skip" };
  if (r != nullptr) {
    cName = r->getElementName();
    pre = getPreMsg(r->isPrevious());
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultText = "before arbitrate skip";
  } else {
    if (cs != nullptr) {
      resultText = cs->getElementName() + " : " + std::to_string(result);
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      "
      + pre
      + "Content["
      + cName
      + "] state value ["
      + resultText
      + "]");
#endif
  return result;
}

#ifdef RBA_USE_LOG
const std::string
RBAStateValue::getSymbol() const
{
  return ".stateValue()";
}
#endif

}

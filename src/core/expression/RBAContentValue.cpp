/// コンテントバリュークラス定義ファイル

#include <string>
#include "RBAContentValue.hpp"
#include "RBAAllocatable.hpp"
#include "RBAContentState.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAContentValue::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテント状態の価値にacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAContentValue::getModelElementType() const
{
  return RBAModelElementType::ContentValue;
}

std::int32_t
RBAContentValue::getValueCore(RBAConstraintInfo* info, RBAArbitrator* arb) const
{
  std::int32_t result { -99 };
  const auto leftInfo = info->getChild(0U);
  const auto r = getLhsOperand()->getReferenceObject(leftInfo, arb);
  const RBAContentState* cs { nullptr };
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (r != nullptr) {
      const auto a = dynamic_cast<const RBAAllocatable*>(r->getRawObject());
      if (a != nullptr) {
        if (r->isPrevious()) {
          cs = arb->getResult()->getDirectPreContentState(a);
          if (cs != nullptr) {
            result = cs->getContentStatePriority();
          }
        } else {
          info->addOperandAllocatable(a);
          if (a->isChecked()) {
            cs = a->getState();
            if (cs != nullptr) {
              result = cs->getContentStatePriority();
            }
          } else {
            // 今回調停が終わっていない場合はExceptionを投げる
            info->setExceptionBeforeArbitrate(true);
          }
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string pre;
  std::string aName = "NULL";
  std::string resultText = "no Content skip";
  if (r != nullptr) {
    aName = r->getElementName();
    pre = getPreMsg(r->isPrevious());
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultText = "before arbitrate skip";
  } else {
    if (cs != nullptr) {
      resultText = cs->getOwner()->getElementName() + "::" + cs->getElementName() + " : " + cs->getPriorityString();
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      "
      + pre
      + "Allocatable["
      + aName
      + "] has Content Priority ["
      + resultText
      + "]");
  #endif
  return result;
}
#ifdef RBA_USE_LOG
const std::string
RBAContentValue::getSymbol() const
{
  return ".contentValue()";
}
#endif
}

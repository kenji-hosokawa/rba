/// Attenuatedチェッククラス定義ファイル

#include "RBAIsAttenuated.hpp"

#include "RBAExpression.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAResultImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsAttenuated::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsAttenuated::getModelElementType() const
{
  return RBAModelElementType::IsAttenuated;
}

bool
RBAIsAttenuated::executeCore(RBAConstraintInfo* info,
                                 RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if ((leftInfo->isExceptionBeforeArbitrate() ) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAZoneImpl* const zone {dynamic_cast<const RBAZoneImpl*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(zone);
    if (ruleObj->isPrevious() == true) {
      isPassed = arb->getResult()->isPreAttenuated(zone);
    } else {
      if (zone->isAttenuateChecked() == true) {
        isPassed = zone->isAttenuated();
        if (isPassed == true) {
          info->addTrueAllocatable(zone);
        } else {
          info->addFalseAllocatable(zone);
        }
      } else {
        info->setExceptionBeforeArbitrate(true);
      }
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAZoneImpl* zone = dynamic_cast<const RBAZoneImpl*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] true");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // 現時点では、アロケータブルとしてnullを返す式はないので、このパスを通ることはない。
    // 将来、nullを返す式が追加されるかもしれないのでこのままにしておく。
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + "NULL" + getSymbol()
              + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + "NULL" + getSymbol()
              + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  }
#endif
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsAttenuated::getSymbol() const
{
  return ".isAttenuated()";
}

RBAExpressionType
RBAIsAttenuated::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

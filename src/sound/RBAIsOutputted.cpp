/// Outputtedチェッククラス定義ファイル

#include "RBAIsOutputted.hpp"
#include "RBAArbitrator.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAResultImpl.hpp"
#include "RBAContentState.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsOutputted::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsOutputted::getModelElementType() const
{
  return RBAModelElementType::IsOutputted;
}

bool
RBAIsOutputted::executeCore(RBAConstraintInfo* info,
                                RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if ((leftInfo->isExceptionBeforeArbitrate()) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAAllocatable* const zone {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(zone);
    if (ruleObj->isPrevious() == true) {
      if ((arb->getResult()->isPreHidden(zone) == false)
          && (arb->getResult()->getPreAllocatedContentState(zone) != nullptr)) {
        isPassed = true;
      }
    } else {
      if ((zone->isHiddenChecked()==true) && (zone->isHidden()==true)) {
        info->addFalseAllocatable(zone);
      } else {
        if (zone->isChecked()) {
          if (zone->getState() != nullptr) {
            info->clearFalseAllocatable();
            info->addTrueAllocatable(zone);
            isPassed = true;
          } else {
            info->addFalseAllocatable(zone);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAAllocatable* zone = dynamic_cast<const RBAAllocatable*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Zone[" + zone->getElementName()
          + "] is before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      const RBAContentState* contentState;
      if (ruleObj->isPrevious() == true) {
        contentState = arb->getResult()->getPreAllocatedContentState(zone);
      } else {
        contentState = zone->getState();
      }
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Zone["
              + zone->getElementName() + "] is Outputted Content["
              + contentState->getOwner()->getElementName() + "::"
              + contentState->getElementName() + "]");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Zone["
              + zone->getElementName() + "] is not Outputted");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else if (info->isExceptionBeforeArbitrate() == true) {
    // 現時点では、Allocatableとしてnullを返す式は存在しないため、このパスは通らない
    // 将来追加されるかもしれないので、残しておく
    LOG_arbitrateConstraintLogicLogLine(
        "      Zone[NULL] is not Outputted");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  }
#endif
  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsOutputted::getSymbol() const
{
  return ".isOutputted()";
}

RBAExpressionType
RBAIsOutputted::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

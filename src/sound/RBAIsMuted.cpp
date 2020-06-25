/// Mutedチェッククラス定義ファイル

#include "RBAIsMuted.hpp"
#include "RBAArbitrator.hpp"
#include "RBAResultImpl.hpp"
#include "RBAAllocatable.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsMuted::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsMuted::getModelElementType() const
{
  return RBAModelElementType::IsMuted;
}

bool
RBAIsMuted::executeCore(RBAConstraintInfo* info,
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
    if (ruleObj->isPrevious() == false) {
      if (zone->isHiddenChecked() == false) {
        info->setExceptionBeforeArbitrate(true);
      } else if (zone->isHidden() == true) {
        isPassed = true;
        info->addTrueAllocatable(zone);
      } else {
        info->addFalseAllocatable(zone);
      }
    } else {
      isPassed = arb->getResult()->isPreHidden(zone);
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAAllocatable* zone = dynamic_cast<const RBAAllocatable*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + zone->getElementName() + getSymbol()
              + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getElementName()
              + getSymbol() + "] true");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getElementName()
              + getSymbol() + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // 現時点では、Allocatableとしてnullを返すパターンはないので、このパスを通ることはない。
    // 将来、追加されるかもしれないので残しておく。
    LOG_arbitrateConstraintLogicLogLine(
        "      [NULL" + getSymbol() + "] false");
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
RBAIsMuted::getSymbol() const
{
  return ".isMuted()";
}

RBAExpressionType
RBAIsMuted::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

/// Hiddenチェッククラス定義ファイル

#include "RBAIsHidden.hpp"

#include "RBAArbitrator.hpp"
#include "RBAAllocatable.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAResultImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAIsHidden::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsHidden::getModelElementType() const
{
  return RBAModelElementType::IsHidden;
}

bool
RBAIsHidden::executeCore(RBAConstraintInfo* info,
                         RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if ((leftInfo->isExceptionBeforeArbitrate()) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAAllocatable* const area {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(area);
    if (ruleObj->isPrevious() == false) {
      if (area->isHiddenChecked() == false) {
        info->setExceptionBeforeArbitrate(true);
      } else if (area->isHidden() == true) {
        isPassed = true;
        info->addTrueAllocatable(area);
      } else {
        info->addFalseAllocatable(area);
      }
    } else {
      isPassed = arb->getResult()->isPreHidden(area);
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAAllocatable* area = dynamic_cast<const RBAAllocatable*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + area->getElementName() + getSymbol()
              + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + area->getElementName()
              + getSymbol() + "] true");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + area->getElementName()
              + getSymbol() + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // 現時点では、AllocatableとしてNULLを返す式はないので、このパスは通らないが、
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
RBAIsHidden::getSymbol() const
{
  return ".isHidden()";
}

RBAExpressionType
RBAIsHidden::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

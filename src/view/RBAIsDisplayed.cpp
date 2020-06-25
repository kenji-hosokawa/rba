/// Displayedチェッククラス定義ファイル

#include "RBAIsDisplayed.hpp"

#include "RBAExpression.hpp"
#include "RBAAllocatable.hpp"
#include "RBARuleObject.hpp"
#include "RBAContentState.hpp"
#include "RBAArbitrator.hpp"
#include "RBAResultImpl.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAIsDisplayed::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsDisplayed::getModelElementType() const
{
  return RBAModelElementType::IsDisplayed;
}

bool
RBAIsDisplayed::executeCore(RBAConstraintInfo* info,
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
    const RBAAllocatable* const allocatable {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(allocatable);
    if (ruleObj->isPrevious() == true) {
      if ((arb->getResult()->isPreHidden(allocatable) == false)
          && (arb->getResult()->getPreAllocatedContentState(allocatable)
              != nullptr)) {
        isPassed = true;
      }
    } else {
      if ((allocatable->isHiddenChecked() == true)
          && (allocatable->isHidden() == true)) {
        info->addFalseAllocatable(allocatable);
      } else {
        if (allocatable->isChecked() == true) {
          if (allocatable->getState() != nullptr) {
            info->addTrueAllocatable(allocatable);
            isPassed = true;
          } else {
            info->addFalseAllocatable(allocatable);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string lhsName;
  const RBAAllocatable* allocatable = nullptr;
  if (ruleObj == nullptr) {
    // 現時点では、Allocatableとしてnullを返す式はないので、このパスを通ることはない
    // 将来、nullを返す式が追加されるかもしれないので残しておく
    lhsName = "NULL";
  } else {
    allocatable = dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject());
    lhsName = allocatable->getElementName();
  }
  if (info->isExceptionBeforeArbitrate() == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    const RBAContentState* contentState;
    if (ruleObj->isPrevious() == true) {
      contentState = arb->getResult()->getPreAllocatedContentState(allocatable);
    } else {
      contentState = allocatable->getState();
    }
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is Displayed Content["
        + contentState->getOwner()->getElementName()
            + "::" + contentState->getElementName() + "]");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is not Displayed");
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
RBAIsDisplayed::getSymbol() const
{
  return ".isDisplayed()";
}

RBAExpressionType
RBAIsDisplayed::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

/// Soundingチェッククラス定義ファイル

#include <algorithm>

#include "RBAAllocatable.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExecuteResult.hpp"
#include "RBAExpressionType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAIsSounding.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAResultImpl.hpp"

namespace rba
{

void
RBAIsSounding::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsSounding::getModelElementType() const
{
  return RBAModelElementType::IsSounding;
}

bool
RBAIsSounding::executeCore(RBAConstraintInfo* info,
                           RBAArbitrator* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* content {nullptr};
  if (ruleObj != nullptr) {
    content = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }
  if (leftInfo->isExceptionBeforeArbitrate() || (content == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj->isPrevious() == false) {
    const RBAContentState* const contentState
      {arb->getResult()->getActiveState(content)};
    if (contentState != nullptr) {
      for(const RBAAllocatable* const allocatable : content->getAllocatables()) {
        info->addOperandAllocatable(allocatable);
        if (allocatable->isChecked() == true) {
          const RBAContentState* const allocateContentState {allocatable->getState()};
          if (contentState == allocateContentState) {
            if ((allocatable->isHiddenChecked() == true)
                && (allocatable->isHidden() == true)) {
              info->addFalseAllocatable(allocatable);
            } else {
              info->setExceptionBeforeArbitrate(false);
              info->clearFalseAllocatable();
              info->addTrueAllocatable(allocatable);
              isPassed = true;
              break;
            }
          } else {
            info->addFalseAllocatable(allocatable);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    } else{
      for(const auto a:content->getAllocatables()){
        info->addFalseAllocatable(a);
      }
    }
  } else {
    const RBAContentState* const contentState
      {arb->getResult()->getPreActiveState(content)};
    if (contentState != nullptr) {
      for(const RBAAllocatable* const allocatable : content->getAllocatables()) {
        info->addOperandAllocatable(allocatable);
        const RBAContentState* const allocateContentState
        {arb->getResult()->getPreAllocatedContentState(allocatable)};
        if ((contentState == allocateContentState)
            && (arb->getResult()->isPreHidden(allocatable) == false)) {
          isPassed = true;
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    if (content != nullptr) {
    LOG_arbitrateConstraintLogicLogLine(
        "      Content[" + content->getElementName()
        + "] before arbitrate skip");
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      Content[NULL] before arbitrate skip");
    }
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    const RBAContentState* contentState;
    if (ruleObj->isPrevious() == false) {
      contentState = arb->getResult()->getActiveState(content);
    } else {
      contentState = arb->getResult()->getPreActiveState(content);
    }
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "::" + contentState->getElementName()
        + "] is Sounding");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "] is not Sounding");
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
RBAIsSounding::getSymbol() const
{
  return ".isSounding()";
}

RBAExpressionType RBAIsSounding::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

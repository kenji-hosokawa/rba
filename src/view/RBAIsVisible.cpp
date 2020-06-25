/// ビジブルチェッククラス定義ファイル

#include "RBAAllocatable.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExecuteResult.hpp"
#include "RBAExpressionType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAIsVisible.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAResultImpl.hpp"

namespace rba
{

void RBAIsVisible::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsVisible::getModelElementType() const
{
  return RBAModelElementType::IsVisible;
}

bool
RBAIsVisible::executeCore(RBAConstraintInfo* info,
                          RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
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
        const RBAContentState* const allocateContentState {allocatable->getState()};
        if (allocatable->isChecked() == true) {
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
    } else {
      for (auto& a : content->getAllocatables()) {
        info->addFalseAllocatable(a);
      }
    }
  } else {
    const RBAContentState* const contentState {arb->getResult()->getPreActiveState(content)};
    if (contentState != nullptr) {
      for(const RBAAllocatable* const allocatable : content->getAllocatables()) {
        info->addOperandAllocatable(allocatable);
        const RBAContentState* const allocateContentState {arb->getResult()->getPreAllocatedContentState(allocatable)};
        if ((contentState == allocateContentState)
            && (arb->getResult()->isPreHidden(allocatable) == false)) {
          isPassed = true;
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    if(content == nullptr) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Content[NULL] is not Visible");
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
          + content->getElementName() + "] is before arbitrate skip");
    }
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    const RBAContentState* contentState;
    if (ruleObj->isPrevious() == true) {
      contentState = arb->getResult()->getPreActiveState(content);
    } else {
      contentState = arb->getResult()->getActiveState(content);
    }
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "::" + contentState->getElementName()
        + "] is Visible");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "] is not Visible");
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
RBAIsVisible::getSymbol() const
{
  return ".isVisible()";
}

RBAExpressionType
RBAIsVisible::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

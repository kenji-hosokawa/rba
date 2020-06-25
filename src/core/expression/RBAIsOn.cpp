/**
 * シーンのアクティブ判定クラスの定義ファイル
 */

#include "RBAIsOn.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBASceneImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAIsOn::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsOn::getModelElementType() const
{
  return RBAModelElementType::IsOn;
}

bool
RBAIsOn::executeCore(RBAConstraintInfo* info,
                     RBAArbitrator* arb) const
{
  bool isPassed {false};
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr){
    const RBASceneImpl* const scene {dynamic_cast<const RBASceneImpl*>(ruleObj->getRawObject())};
    if (ruleObj->isPrevious() == false) {
      isPassed = arb->getResult()->isActive(scene);
    } else {
      isPassed = arb->getResult()->isPreActive(scene);
    }
  } else {
    // 現時点では、sceneとしてnullを返す式は存在しないため、このパスを通ることはないが、
    // 将来、nullを返す式が追加されるかもしれないのでこのままにしておく。
    ;
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBASceneImpl* scene = dynamic_cast<const RBASceneImpl*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Scene[" + scene->getName() + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Scene["
              + scene->getName() + "] is On");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Scene["
              + scene->getName() + "] is not On");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // 現時点では、sceneとしてnullを返す式は存在しないため、このパスを通ることはないが、
    // 将来、nullを返す式が追加されるかもしれないのでこのままにしておく。
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Scene[NULL] is not On");
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
RBAIsOn::getSymbol() const
{
  return ".isOn()";
}

const std::string
RBAIsOn::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string RBAIsOn::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}

RBAExpressionType
RBAIsOn::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

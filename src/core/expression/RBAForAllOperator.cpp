/**
 * ForAllオペレータクラス定義ファイル
 */

#include "RBAForAllOperator.hpp"

#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALambdaExpression.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAForAllOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAForAllOperator::getModelElementType() const
{
  return RBAModelElementType::ForAllOperator;
}

bool
RBAForAllOperator::executeCore(RBAConstraintInfo* info,
				   RBAArbitrator * arb) const
{
  const RBAExpression* const setObj {getLhsOperand()};
  RBALambdaExpression* const lambda {getLambda()};

  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());

  // ルールオブジェクトを取得してループ
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  std::vector<const RBARuleObject*> objs;
  const RBARuleObject* const ruleObj {setObj->getReferenceObject(leftInfo, arb)};
  const RBARuleObject* objset {nullptr};
  if (ruleObj != nullptr) {
    objset = ruleObj->getRawObject();
  }

  if(leftInfo->isExceptionBeforeArbitrate() || (objset == nullptr)) {
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();

    info->setExceptionBeforeArbitrate(true);
    return false;
  }
  if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
    objs.clear();
    for(const RBAAllocatable* alloc
	  : dynamic_cast<const RBAAllocatableSet*>(objset)->getLeafAllocatable()) {
      objs.push_back(alloc);
    }
  }
  else {
    objs.clear();
    for(const auto& cont : dynamic_cast<const RBAContentSet*>(objset)->getLeafContent() ){
      objs.push_back(cont);
    }
  }

  bool isTrue {true};
  std::uint32_t i {0U};
  for(const RBARuleObject* const obj : objs) {
    // カバレッジ向けの制約階層構造に回数を追加
    LOG_addHierarchy("#" + std::to_string(i));

    RBAConstraintInfo* const childInfo {info->getChild(i)};
    lambda->setRuleObj(obj);

    const bool res {lambda->execute(childInfo, arb)};

    // カバレッジ向けの制約階層構造から回数を削除
    LOG_removeHierarchy();

    if(childInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    } else {
      isTrue = (isTrue && res);
    }
    i++;
  }

  if (isTrue == false) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();
    info->setExceptionBeforeArbitrate(false);
    return false;
  } else if (info->isExceptionBeforeArbitrate()) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();
    return false;
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] true");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();
    return true;
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAForAllOperator::getSymbol() const
{
  return "For All";
}

const std::string
RBAForAllOperator::getExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  return getSymbol() + " "
    + exprLhs->getExpressionText() + " "
    + getLambda()->getExpressionText();
}

const std::string
RBAForAllOperator::getCoverageExpressionText() const
{
  getLambda()->clearRuleObj();
  RBAExpression* exprLhs = getLhsOperand();
  return getSymbol() + " "
    + exprLhs->getCoverageExpressionText() + " "
    + getLambda()->getCoverageExpressionText();
}

RBAExpressionType
RBAForAllOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

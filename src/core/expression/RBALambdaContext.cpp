/**
 * ラムダコンテキストクラス定義ファイル
 */

#include "RBALambdaContext.hpp"
#include "RBALogManager.hpp"
#include "RBAVariable.hpp"
#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBALambdaExpression* const
RBALambdaContext::getLambda() const
{
  return lambda_;
}

void
RBALambdaContext::setLambda(RBALambdaExpression* const newLambda)
{
  lambda_ = newLambda;
}

#ifdef RBA_USE_LOG
void
RBALambdaContext::createHierarchy()
{
  lambda_->getX()->clearRuleObj();
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  // ルールオブジェクトを取得してループ
  RBAExpression* setObj = getLhsOperand();
  RBAConstraintInfo dummyInfo;
  // For-AllやExistsの集合に用いるAllInstanceOf...やSetOfOperatorでは参照しないため、nullptrで問題ない
  RBAArbitrator* dummyArb = nullptr;
  const RBARuleObject* objset = setObj->getReferenceObject(&dummyInfo, dummyArb);
  std::vector<const RBARuleObject*> objs;
  if(objset) {
    if(dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      const RBAAllocatableSet* aSet
	= dynamic_cast<const RBAAllocatableSet*>(objset);
      for(const auto& alloc : aSet->getLeafAllocatable()) {
	objs.push_back(alloc);
      }
    }
    else if(dynamic_cast<const RBAContentSet*>(objset) != nullptr) {
      const RBAContentSet* cSet = dynamic_cast<const RBAContentSet*>(objset);
      for(const auto& cont : cSet->getLeafContent() ){
	objs.push_back(cont);
      }
    }
  }

  // カバレッジログで自分が持つ変数の展開を有効にする
  std::int32_t idx=0;
  for(const RBARuleObject* obj : objs) {
    LOG_addHierarchy("#" + std::to_string(idx++));
    lambda_->getX()->setRuleObj(obj);
    lambda_->createHierarchy();
    LOG_removeHierarchy();
  }

  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
}
#endif

}

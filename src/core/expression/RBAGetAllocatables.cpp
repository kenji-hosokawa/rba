/**
 * アロケータブル取得クラス定義ファイル
 */

#include "RBAGetAllocatables.hpp"

#include "RBAContent.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAGetAllocatables::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテントにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAGetAllocatables::getModelElementType() const
{
  return RBAModelElementType::GetAllocatables;
}

const RBARuleObject*
RBAGetAllocatables::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitrator* arb) const
{
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* content {nullptr};
  if (ruleObj != nullptr) {
    content = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  if (content == nullptr) {
    if (leftInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    }
    return nullptr;
  }

  return content->getAllocatableSet();
}

#ifdef RBA_USE_LOG
const std::string
RBAGetAllocatables::getSymbol() const
{
  return ".allocatables()";
}

const std::string
RBAGetAllocatables::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

// 現時点では調停FWは、GetAllocatablesのcreateHierarchy()を呼び出す
// 制約式がかけないため、このパスを通ることはない。
// 将来の変更で通る可能性があるので、このまま残しておく。
void
RBAGetAllocatables::createHierarchy()
{
  // 構造に影響しないので何もしない
}

#endif

}

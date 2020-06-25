/**
 * コンテントリスト取得クラス定義ファイル
 */

#include "RBAGetContentsList.hpp"

#include "RBAAllocatable.hpp"
#include "RBAContentSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAGetContentsList::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // コンテントにacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAGetContentsList::getModelElementType() const
{
  return RBAModelElementType::GetContentsList;
}

const RBARuleObject*
RBAGetContentsList::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitrator* arb) const
{
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAAllocatable* allocatable {nullptr};
  if (ruleObj != nullptr) {
    allocatable = dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject());
  }
  // この制約式で参照するコンテンツが前回の調停結果なのかを示す

  if (leftInfo->isExceptionBeforeArbitrate() || (allocatable == nullptr)) {
    // 現時点では調停FWは、GetContentsList以下の式が調停前となる及び、
    // allocatableとしてnullを返す制約式がかけないため、このパスを通ることはない。
    // 将来の変更で通る可能性があるので、このまま残しておく。
    info->setExceptionBeforeArbitrate(true);
    return nullptr;
  }

  return allocatable->getContentSet();
}

#ifdef RBA_USE_LOG
// 現時点では調停FWは、GetContentsListのcreateHierarchy()を呼び出す
// 制約式がかけないため、このパスを通ることはない。
// 将来の変更で通る可能性があるので、このまま残しておく。
void
RBAGetContentsList::createHierarchy()
{
  // 構造に影響しないので何もしない
}
#endif

}

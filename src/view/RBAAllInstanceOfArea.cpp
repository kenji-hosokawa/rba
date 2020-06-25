/**
 * AllInstanceOfArea実装クラス定義ファイル
 */

#include "RBAAllInstanceOfArea.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfArea::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // For-All,Existsの集合にacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfArea::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfArea;
}

const RBARuleObject*
RBAAllInstanceOfArea::getReferenceObjectCore(RBAConstraintInfo* info,
                                             RBAArbitrator* arb) const
{
  return &allAreaSet_;
}

void
RBAAllInstanceOfArea::setAreas(const std::list<const RBAAreaImpl*>& areas)
{
  for (auto& a : areas) {
    allAreaSet_.addTarget(a);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfArea::getExpressionText() const
{
  return "ALL_AREAS";
}

const std::string
RBAAllInstanceOfArea::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}

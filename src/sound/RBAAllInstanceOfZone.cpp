/**
 * ゾーンの全インスタンスクラス定義ファイル
 */

#include "RBAAllInstanceOfZone.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfZone::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // For-All,Existsの集合にacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfZone::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfZone;
}

const RBARuleObject*
RBAAllInstanceOfZone::getReferenceObjectCore(RBAConstraintInfo* info,
                                             RBAArbitrator* arb) const
{
  return &allZoneSet_;
}

void
RBAAllInstanceOfZone::setZones(const std::list<const RBAZoneImpl*> zones)
{
  for (auto& content : zones) {
    allZoneSet_.addTarget(content);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfZone::getExpressionText() const
{
  return "ALL_ZONES";
}

const std::string
RBAAllInstanceOfZone::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}

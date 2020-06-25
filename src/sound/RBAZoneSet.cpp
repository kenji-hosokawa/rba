/**
 * ゾーンセットクラス定義ファイル
 */

#include "RBAZoneSet.hpp"
#include "RBAZone.hpp"
#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAZoneSet::RBAZoneSet(const std::string& name)
  : RBARuleObject{name},
    RBAAllocatableSet{name}
{
}

const std::list<const RBAZone*>&
RBAZoneSet::getTargets() const
{
  return externZones_;
}

void
RBAZoneSet::addTarget(const RBAAllocatable* alloc)
{
  RBAAllocatableSet::addTarget(alloc);
  externZones_.push_back(dynamic_cast<const RBAZone*>(alloc));
}

void
RBAZoneSet::clear()
{
  RBAAllocatableSet::clear();
  externZones_.clear();
}

RBAModelElementType
RBAZoneSet::getModelElementType() const
{
  return RBAModelElementType::ZoneSet;
}

}

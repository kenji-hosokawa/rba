/**
 * エリアセットクラス定義ファイル
 */

#include "RBAAreaSet.hpp"
#include "RBAArea.hpp"
#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAAreaSet::RBAAreaSet(const std::string& name)
  : RBARuleObject{name},
    RBAAllocatableSet{name}
{
}

const std::list<const RBAArea*>&
RBAAreaSet::getTargets() const
{
  return externAreas_;
}

void
RBAAreaSet::addTarget(const RBAAllocatable* alloc)
{
  RBAAllocatableSet::addTarget(alloc);
  externAreas_.push_back(dynamic_cast<const RBAArea*>(alloc));
}

void
RBAAreaSet::clear()
{
  RBAAllocatableSet::clear();
  externAreas_.clear();
}

RBAModelElementType
RBAAreaSet::getModelElementType() const
{
  return RBAModelElementType::AreaSet;
}

}

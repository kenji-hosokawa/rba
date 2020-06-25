/// @file  RBAZoneSetMaker.cpp
/// @brief ZoneSetオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAZoneSetMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAZoneSet.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAZoneSetMaker::RBAZoneSetMaker()
  : RBARuleObjectMaker{"zonesets"},
    RBAAllocatableSetMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAZoneSetMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAZoneSet>(name);
}

RBAModelElement*
RBAZoneSetMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  static_cast<void>(RBAAllocatableSetMaker::setProperty(element, jsonElem, model, owner));

  RBAZoneSet* const zoneSet {dynamic_cast<RBAZoneSet*>(element)};

  model->addZoneSet(zoneSet);

  return zoneSet;
}

}

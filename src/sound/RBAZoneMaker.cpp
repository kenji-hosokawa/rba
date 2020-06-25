/// @file  RBAZoneMaker.cpp
/// @brief Zoneオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAZoneMaker.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAZoneMaker::RBAZoneMaker()
  : RBARuleObjectMaker{"zones"},
    RBAAllocatableMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAZoneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAZoneImpl>(name);
}

RBAModelElement*
RBAZoneMaker::setProperty(RBAModelElement* element,
                          const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner)
{
  element = RBAAllocatableMaker::setProperty(element, jsonElem, model, owner);
  if(element == nullptr) {
    return nullptr;
  }

  RBAZoneImpl* const zone {dynamic_cast<RBAZoneImpl*>(element)};

  return zone;
}

}

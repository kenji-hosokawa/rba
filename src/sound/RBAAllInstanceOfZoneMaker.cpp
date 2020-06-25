/// @file  RBAAllInstanceOfZoneMaker.cpp
/// @brief AllInstanceOfZoneオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllInstanceOfZoneMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfZone.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfZoneMaker::RBAAllInstanceOfZoneMaker()
  : RBAExpressionMaker{"AllInstanceOfZone"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfZoneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfZone>();
}

RBAModelElement*
RBAAllInstanceOfZoneMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  RBAAllInstanceOfZone* const allInstZone
    {dynamic_cast<RBAAllInstanceOfZone*>(element)};

  // Set zone
  allInstZone->setZones(model->getZoneImpls());

  return allInstZone;
}

}

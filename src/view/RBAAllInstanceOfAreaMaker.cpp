/// @file  RBAAllInstanceOfAreaMaker.cpp
/// @brief AllInstanceOfAreaオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllInstanceOfAreaMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfArea.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfAreaMaker::RBAAllInstanceOfAreaMaker()
  : RBAExpressionMaker{"AllInstanceOfArea"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfAreaMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfArea>();
}

RBAModelElement*
RBAAllInstanceOfAreaMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  RBAAllInstanceOfArea* const allArea
    {dynamic_cast<RBAAllInstanceOfArea*>(element)};
  allArea->setAreas(model->getAreaImpls());

  return allArea;
}

}

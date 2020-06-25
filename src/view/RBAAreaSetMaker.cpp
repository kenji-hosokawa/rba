/// @file  RBAAreaSetMaker.cpp
/// @brief AreaSetオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAreaSetMaker.hpp"
#include "RBAAreaSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAreaSetMaker::RBAAreaSetMaker()
  : RBARuleObjectMaker{"areasets"},
    RBAAllocatableSetMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAAreaSetMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAreaSet>(name);
}

RBAModelElement*
RBAAreaSetMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  static_cast<void>(RBAAllocatableSetMaker::setProperty(element, jsonElem, model, owner));

  RBAAreaSet* const areaSet {dynamic_cast<RBAAreaSet*>(element)};

  model->addAreaSet(areaSet);

  return areaSet;
}

}

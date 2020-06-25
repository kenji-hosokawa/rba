/// @file  RBAAllInstanceOfSoundContentMaker.cpp
/// @brief AllInstanceOfSoundContentオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllInstanceOfSoundContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfSoundContent.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfSoundContentMaker::RBAAllInstanceOfSoundContentMaker()
  : RBAExpressionMaker{"AllInstanceOfSoundContent"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfSoundContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfSoundContent>();
}

RBAModelElement*
RBAAllInstanceOfSoundContentMaker::setProperty(RBAModelElement* element,
                                               const RBAJsonElement* jsonElem,
                                               RBAModelImpl* model,
                                               RBAModelElement* owner)
{
  RBAAllInstanceOfSoundContent* const allSoundCont
    {dynamic_cast<RBAAllInstanceOfSoundContent*>(element)};

  // Set sound content
  allSoundCont->setContents(model->getSoundContentImpls());

  return allSoundCont;
}

}

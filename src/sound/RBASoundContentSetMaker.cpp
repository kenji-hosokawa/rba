/// @file  RBASoundContentSetMaker.cpp
/// @brief SoundContentSetオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASoundContentSetMaker.hpp"
#include "RBASoundContentSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASoundContentSetMaker::RBASoundContentSetMaker()
  : RBARuleObjectMaker{"soundcontentsets"},
    RBAContentSetMaker()
{
}

std::unique_ptr<RBAModelElement>
RBASoundContentSetMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASoundContentSet>(name);
}

RBAModelElement*
RBASoundContentSetMaker::setProperty(RBAModelElement* element,
                                     const RBAJsonElement* jsonElem,
                                     RBAModelImpl* model,
                                     RBAModelElement* owner)
{
  static_cast<void>(RBAContentSetMaker::setProperty(element, jsonElem, model, owner));

  const auto contentSet = dynamic_cast<RBASoundContentSet*>(element);

  model->addSoundContentSet(contentSet);

  return contentSet;
}

}
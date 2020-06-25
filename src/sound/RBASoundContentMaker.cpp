/// @file  RBASoundContentMaker.cpp
/// @brief SoundContentオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASoundContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBASoundContentStateMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASoundContentMaker::RBASoundContentMaker()
  : RBARuleObjectMaker{"soundcontents"},
    RBAContentMaker()
{
}

std::unique_ptr<RBAModelElement>
RBASoundContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASoundContentImpl>(name);
}

RBAModelElement*
RBASoundContentMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  element = RBAContentMaker::setProperty(element, jsonElem, model, owner);
  if(element == nullptr) {
    return nullptr;
  }

  RBASoundContentImpl* const content {dynamic_cast<RBASoundContentImpl*>(element)};

  return content;
}

}

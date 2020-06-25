/// @file  RBASoundContentStateMaker.cpp
/// @brief SoundContentStateオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASoundContentStateMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASoundContentStateMaker::RBASoundContentStateMaker()
  : RBAContentStateMaker{"SoundContentState"}
{
}

std::unique_ptr<RBAModelElement>
RBASoundContentStateMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASoundContentStateImpl>(name);
}

RBAModelElement*
RBASoundContentStateMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  // unique_ptrのインスタンスを生成して、modelに登録する。
  // name, priority, ownerもセットしている。
  RBAModelElement* const elem {RBAContentStateMaker::setProperty(element, jsonElem, model, owner)};
  if(elem == nullptr) {
    return nullptr;
  }
  RBASoundContentStateImpl* const state
    {dynamic_cast<RBASoundContentStateImpl*>(elem)};

  return state;
}

}

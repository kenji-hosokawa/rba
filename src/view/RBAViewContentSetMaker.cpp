/// @file  RBAViewContentSetMaker.cpp
/// @brief ViewContentSetオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAViewContentSetMaker.hpp"
#include "RBAViewContentSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAViewContentSetMaker::RBAViewContentSetMaker()
  : RBARuleObjectMaker{"viewcontentsets"},
    RBAContentSetMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAViewContentSetMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAViewContentSet>(name);
}

RBAModelElement*
RBAViewContentSetMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(RBAContentSetMaker::setProperty(element, jsonElem, model, owner));

  const auto contentSet = dynamic_cast<RBAViewContentSet*>(element);

  model->addViewContentSet(contentSet);

  return contentSet;
}

}

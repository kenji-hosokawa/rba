/// @file  RBAViewContentMaker.cpp
/// @brief ViewContentオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAViewContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBASizeMaker.hpp"
#include "RBAViewContentStateMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAViewContentMaker::RBAViewContentMaker()
  : RBARuleObjectMaker{"viewcontents"},
    RBAContentMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAViewContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAViewContentImpl>(name);
}

RBAModelElement*
RBAViewContentMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  element = RBAContentMaker::setProperty(element, jsonElem, model, owner);
  if(element == nullptr) {
    return nullptr;
  }

  RBAViewContentImpl* const content {dynamic_cast<RBAViewContentImpl*>(element)};

  // size
  RBASizeMaker szMaker;
  szMaker.setFactory(getFactory());
  for(auto& size : jsonElem->findChildren("size")->getChildren()) {
    const auto sizeInst = szMaker.create(size.get(), model, content);
    content->addSize(dynamic_cast<RBASizeImpl*>(sizeInst));
  }

  return content;
}

}

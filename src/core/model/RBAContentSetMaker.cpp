/// @file  RBAContentSetMaker.cpp
/// @brief ContentSetオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAContentSetMaker.hpp"
#include "RBAContentSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAContentSetMaker::RBAContentSetMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractContentMaker{label}
{
}

RBAModelElement*
RBAContentSetMaker::setProperty(RBAModelElement* element,
                                const RBAJsonElement* jsonElem,
                                RBAModelImpl* model,
                                RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractContentMaker::setProperty(element, jsonElem, model, owner));

  const auto contentSet = dynamic_cast<RBAContentSet*>(element);

  // content
  for(const auto& content : jsonElem->findChildren("target")->getChildren()) {
    const auto cont = model->findContent(content->getName());
    contentSet->addTarget(cont);
  }

  return contentSet;
}

}

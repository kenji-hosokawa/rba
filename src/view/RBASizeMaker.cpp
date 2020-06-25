/// @file  RBASizeMaker.cpp
/// @brief Sizeオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASizeMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASizeMaker::RBASizeMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"Size"}
{
}

RBAModelElement*
RBASizeMaker::create(const RBAJsonElement* jsonElem,
                     RBAModelImpl* model,
                     RBAModelElement* owner)
{
  std::unique_ptr<RBAModelElement> inst
    {createInstance(jsonElem->findChildren("name")->getString())};
  const auto element = inst.get();
  static_cast<void>(model->addSizeInstance(dynamic_cast<RBANamedElement*>(owner)->getElementName(), std::move(inst)));

  return setProperty(element, jsonElem, model, owner);
}

std::unique_ptr<RBAModelElement>
RBASizeMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASizeImpl>(name);
}

RBAModelElement*
RBASizeMaker::setProperty(RBAModelElement* element,
                          const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner)
{
  RBASizeImpl* const size {dynamic_cast<RBASizeImpl*>(element)};

  // Set width
  size->setWidth(jsonElem->findChildren("width")->getInt());
  // Set height
  size->setHeight(jsonElem->findChildren("height")->getInt());

  return size;
}

}

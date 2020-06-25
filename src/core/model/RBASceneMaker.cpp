/// @file  RBASceneMaker.cpp
/// @brief Sceneオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASceneMaker.hpp"
#include "RBASceneImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

RBASceneMaker::RBASceneMaker()
  : RBARuleObjectMaker{"scenes"}
{
}

std::unique_ptr<RBAModelElement>
RBASceneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASceneImpl>(name);
}

RBAModelElement*
RBASceneMaker::setProperty(RBAModelElement* element,
                           const RBAJsonElement* jsonElem,
                           RBAModelImpl* model,
                           RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));

  RBASceneImpl* const scene {dynamic_cast<RBASceneImpl*>(element)};

  // Set global
  const std::string global {jsonElem->findChildren("global")->getString()};
  if(global == "true") {
    scene->setGlobal(true);
  }
  else {
    scene->setGlobal(false);
  }

  // Set property
  const RBAJsonElement* const properties {jsonElem->findChildren("property")};
  if(properties != nullptr) {
    for(const auto& property : properties->getChildren()) {
      const std::string propertyName {property->findChildren("name")->getString()};
      const std::int32_t value {property->findChildren("value")->getInt()};
      static_cast<void>(scene->addProperty(propertyName, value));
    }
  }

  model->addScene(scene);

  return scene;
}

}

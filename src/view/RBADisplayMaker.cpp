/// @file  RBADisplayMaker.cpp
/// @brief Displayオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBADisplayMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBADisplayImpl.hpp"
#include "RBASizeMaker.hpp"
#include "RBAPositionContainerMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBADisplayMaker::RBADisplayMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"displays"}
{
}

std::unique_ptr<RBAModelElement>
RBADisplayMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBADisplayImpl>(name);
}

RBAModelElement*
RBADisplayMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  RBADisplayImpl* const display {dynamic_cast<RBADisplayImpl*>(element)};

  // Set size
  RBASizeMaker sizeMaker;
  sizeMaker.setFactory(getFactory());
  const RBAModelElement* const size {sizeMaker.create(jsonElem->findChildren("size"), model,
                                           display)};
  display->setSize(dynamic_cast<const RBASizeImpl*>(size));

  // Set position container
  const RBAJsonElement* const jsonPosConts {jsonElem->findChildren("PositionContainer")};
  if(jsonPosConts != nullptr) {
    RBAPositionContainerMaker pcMaker;
    pcMaker.setFactory(getFactory());
    for(const auto& jsonPosCont : jsonPosConts->getChildren()) {
      static_cast<void>(pcMaker.create(jsonPosCont.get(), model, display));
    }
  }

  model->addDisplay(display);

  return display;
}

}

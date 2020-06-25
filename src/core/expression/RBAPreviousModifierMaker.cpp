/// @file  RBAPreviousModifierMaker.cpp
/// @brief PreviousModifierオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAPreviousModifierMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAPreviousModifier.hpp"
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

RBAPreviousModifierMaker::RBAPreviousModifierMaker()
  : RBAExpressionMaker{"PreviousModifier"}
{
}

std::unique_ptr<RBAModelElement>
RBAPreviousModifierMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAPreviousModifier>();
}

RBAModelElement*
RBAPreviousModifierMaker::setProperty(RBAModelElement* element,
                                      const RBAJsonElement* jsonElem,
                                      RBAModelImpl* model,
                                      RBAModelElement* owner)
{
  RBAPreviousModifier* const prevMod {dynamic_cast<RBAPreviousModifier*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, prevMod, jsonElem)};

  // Set object reference
  const RBAJsonElement* const objRefElem {jsonElem->findChildren("objReference")};
  RBAModelElement* const expr {getFactory()->createElement(objRefElem->getClassName(),
                                                     objRefElem)};
  prevMod->setObjReference(dynamic_cast<RBAExpression*>(expr));

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return prevMod;
}

}

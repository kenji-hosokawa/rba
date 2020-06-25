/// @file  RBAVariableMaker.cpp
/// @brief 変数オブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAVariableMaker.hpp"
#include "RBAVariable.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAVariableMaker::RBAVariableMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"Variable"}
{
}

RBAModelElement*
RBAVariableMaker::create(const RBAJsonElement* jsonElem,
                         RBAModelImpl* model,
                         RBAModelElement* owner)
{
  // Variableは同じ名前が存在するので、インスタンスは名前なしで登録する。
  std::unique_ptr<RBAModelElement> inst
    {createInstance(jsonElem->findChildren("name")->getString())};
  const auto element = inst.get();
  static_cast<void>(model->addModelElement(std::move(inst)));

  return setProperty(element, jsonElem, model, owner);
}

std::unique_ptr<RBAModelElement>
RBAVariableMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAVariable>(name);
}

RBAModelElement*
RBAVariableMaker::setProperty(RBAModelElement* element,
                              const RBAJsonElement* jsonElem,
                              RBAModelImpl* model,
                              RBAModelElement* owner)
{
  return element;
}

}

/// @file  RBAIsTypeOfOperatorMaker.cpp
/// @brief IsTypeOfオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsTypeOfOperatorMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsTypeOfOperator.hpp"

namespace rba
{

RBAIsTypeOfOperatorMaker::RBAIsTypeOfOperatorMaker()
  : RBAOperatorMaker{"IsTypeOf"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsTypeOfOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsTypeOfOperator>();
}

RBAModelElement*
RBAIsTypeOfOperatorMaker::setProperty(RBAModelElement* element,
                                      const RBAJsonElement* jsonElem,
                                      RBAModelImpl* model,
                                      RBAModelElement* owner)
{
  RBAIsTypeOfOperator* const isTypeOfOpe
    {dynamic_cast<RBAIsTypeOfOperator*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, isTypeOfOpe, jsonElem)};

  // Set operand
  const RBAJsonElement* const operand {jsonElem->findChildren("operand")};
  const RBAJsonElement* const param {operand->getChild()};
  RBAModelElement* const expr {getFactory()->createElement(param->getClassName(), param)};
  isTypeOfOpe->addOperand(dynamic_cast<RBAExpression*>(expr));
  // Set Tag
  const RBAJsonElement* const tagElem {jsonElem->findChildren("tagName")};
  isTypeOfOpe->setTag(tagElem->getString());

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return isTypeOfOpe;
}

}

/// @file  RBAOperatorMaker.cpp
/// @brief Operatorオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAOperatorMaker.hpp"
#include "RBAOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAOperatorMaker::RBAOperatorMaker(const std::string& label)
  : RBAExpressionMaker{label}
{
}

RBAModelElement*
RBAOperatorMaker::setProperty(RBAModelElement* element,
                              const RBAJsonElement* jsonElem,
                              RBAModelImpl* model,
                              RBAModelElement* owner)
{
  // Create expression
  RBAOperator* const exprOpr {dynamic_cast<RBAOperator*>(element)};

  // Set LetStatement
  const auto pop_num = setLetStatement(model, exprOpr, jsonElem);

  // Set operand
  for(auto& param : jsonElem->findChildren("operand")->getChildren()) {
    const auto expr = getFactory()->createElement(param->getClassName(), param.get());
    exprOpr->addOperand(dynamic_cast<RBAExpression*>(expr));
  }

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return exprOpr;
}

}

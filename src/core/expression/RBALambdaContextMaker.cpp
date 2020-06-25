/// @file  RBALambdaContextMaker.cpp
/// @brief LambdaContextオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBALambdaContextMaker.hpp"
#include "RBALambdaContext.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBALambdaContextMaker::RBALambdaContextMaker(const std::string& label)
  : RBAOperatorMaker{label}
{
}

RBAModelElement*
RBALambdaContextMaker::setProperty(RBAModelElement* element,
                                   const RBAJsonElement* jsonElem,
                                   RBAModelImpl* model,
                                   RBAModelElement* owner)
{
  RBALambdaContext* const lambdaContext
    {dynamic_cast<RBALambdaContext*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, lambdaContext, jsonElem)};
  // Set lambda
  const RBAJsonElement* const lambdaElement {jsonElem->findChildren("lambda")};
  RBAModelElement* const lambdaExpr
    {getFactory()->createElement(lambdaElement->getClassName(), lambdaElement)};
  lambdaContext->setLambda(dynamic_cast<RBALambdaExpression*>(lambdaExpr));
  // Set operand
  const RBAJsonElement* const param {jsonElem->findChildren("operand")->getChild()};
  RBAModelElement* const expr
    {getFactory()->createElement(param->getClassName(), param)};
  lambdaContext->addOperand(dynamic_cast<RBAExpression*>(expr));
  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return lambdaContext;
}

}

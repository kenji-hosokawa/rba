/// @file  RBALambdaExpressionMaker.cpp
/// @brief LambdaExpressionオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBALambdaExpressionMaker.hpp"
#include "RBALambdaExpression.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBALambdaExpressionMaker::RBALambdaExpressionMaker()
  : RBAExpressionMaker{"LambdaExpression"}
{
}

std::unique_ptr<RBAModelElement>
RBALambdaExpressionMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBALambdaExpression>();
}

RBAModelElement*
RBALambdaExpressionMaker::setProperty(RBAModelElement* element,
                                      const RBAJsonElement* jsonElem,
                                      RBAModelImpl* model,
                                      RBAModelElement* owner)
{
  RBALambdaExpression* const lambdaExpr
    {dynamic_cast<RBALambdaExpression*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, lambdaExpr, jsonElem)};

  // Set variable
  const RBAJsonElement* const varElement {jsonElem->findChildren("x")};
  RBAVariable* const var
    {dynamic_cast<RBAVariable*>(getFactory()->createElement("Variable",
                                                         varElement))};
  lambdaExpr->setX(var);
  // Set bodyText
  getFactory()->pushVariable(var);
  const RBAJsonElement* const body {jsonElem->findChildren("bodyText")};
  RBAExpression* const expr
    {dynamic_cast<RBAExpression*>(getFactory()->createElement(body->getClassName(),
                                                           body))};
  lambdaExpr->setBodyText(expr);

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }
  
  return lambdaExpr;
}

}

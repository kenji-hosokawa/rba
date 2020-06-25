/// @file  RBALetActionOperatorMaker.cpp
/// @brief LetActionOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBALetStatementMaker.hpp"
#include "RBALetStatement.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBALetStatementMaker::RBALetStatementMaker()
  : RBAExpressionMaker{"LetStatement"}
{
}

std::unique_ptr<RBAModelElement>
RBALetStatementMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBALetStatement>();
}

RBAModelElement*
RBALetStatementMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  RBALetStatement* const letStmt {dynamic_cast<RBALetStatement*>(element)};

  // Set variable
  const RBAJsonElement* const varElement {jsonElem->findChildren("variable")};
  RBAVariable* const var
    {dynamic_cast<RBAVariable*>(getFactory()->createElement("Variable",
                                                         varElement))};
  letStmt->setVariable(var);
  // Set Body
  getFactory()->pushVariable(var); // popVariable()は本関数の呼び出し元で実行する
  const RBAJsonElement* const body {jsonElem->findChildren("body")};
  RBAExpression* const expr
    {dynamic_cast<RBAExpression*>(getFactory()->createElement(body->getClassName(),
                                                           body))};
  letStmt->addOperand(expr);

  return letStmt;
}

}

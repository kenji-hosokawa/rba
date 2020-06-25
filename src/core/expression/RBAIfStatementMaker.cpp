/// @file  RBAIfStatementMaker.cpp
/// @brief IfActionOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIfStatementMaker.hpp"
#include "RBAIfStatement.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAIfStatementMaker::RBAIfStatementMaker()
  : RBAExpressionMaker{"IfStatement"}
{
}

std::unique_ptr<RBAModelElement>
RBAIfStatementMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIfStatement>();
}

RBAModelElement*
RBAIfStatementMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  RBAIfStatement* const ifstmt {dynamic_cast<RBAIfStatement*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, ifstmt, jsonElem)};

  // Set condition
  const RBAJsonElement* const condElem {jsonElem->findChildren("condition")};
  RBAModelElement* const condExpr
    {getFactory()->createElement(condElem->getClassName(), condElem)};
  ifstmt->setCondition(dynamic_cast<RBAExpression*>(condExpr));
  // Set then
  const RBAJsonElement* const thenElem {jsonElem->findChildren("thenExpression")};
  RBAModelElement* thenExpr {nullptr};
  if(thenElem != nullptr) {
    thenExpr = getFactory()->createElement(thenElem->getClassName(), thenElem);
  }
  ifstmt->setThenExpression(dynamic_cast<RBAExpression*>(thenExpr));
  // Set else
  const RBAJsonElement* const elseElem {jsonElem->findChildren("elseExpression")};
  RBAModelElement* elseExpr {nullptr};
  if(elseElem != nullptr) {
    elseExpr = getFactory()->createElement(elseElem->getClassName(), elseElem);
  }
  ifstmt->setElseExpression(dynamic_cast<RBAExpression*>(elseExpr));

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return ifstmt;
}

}

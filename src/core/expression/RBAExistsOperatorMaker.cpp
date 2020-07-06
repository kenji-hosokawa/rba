/// @file  RBAExistsOperatorMaker.cpp
/// @brief Exists Operator object maker Class definition
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAExistsOperatorMaker.hpp"
#include "RBAExistsOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBAExistsOperatorMaker::RBAExistsOperatorMaker()
  : RBALambdaContextMaker{"ExistsOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAExistsOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAExistsOperator>();
}

RBAModelElement*
RBAExistsOperatorMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBAExistsOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBAExistsOperator>();
}

}

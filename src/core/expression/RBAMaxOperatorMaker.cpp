/// @file  RBAMaxOperatorMaker.cpp
/// @brief MaxOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAMaxOperatorMaker.hpp"
#include "RBAMaxOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBAMaxOperatorMaker::RBAMaxOperatorMaker()
  : RBALambdaContextMaker{"MaxOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAMaxOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAMaxOperator>();
}

RBAModelElement*
RBAMaxOperatorMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBAMaxOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBAMaxOperator>();
}

}

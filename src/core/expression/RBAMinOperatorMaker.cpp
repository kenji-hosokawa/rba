/// @file  RBAMinOperatorMaker.cpp
/// @brief MinOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAMinOperatorMaker.hpp"
#include "RBAMinOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBAMinOperatorMaker::RBAMinOperatorMaker()
  : RBALambdaContextMaker{"MinOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAMinOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAMinOperator>();
}

RBAModelElement*
RBAMinOperatorMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBAMinOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBAMinOperator>();
}

}

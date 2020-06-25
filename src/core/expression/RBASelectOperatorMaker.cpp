/// @file  RBASelectOperatorMaker.cpp
/// @brief SelectOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASelectOperatorMaker.hpp"
#include "RBASelectOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBASelectOperatorMaker::RBASelectOperatorMaker()
  : RBALambdaContextMaker{"SelectOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBASelectOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASelectOperator>();
}

RBAModelElement*
RBASelectOperatorMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBASelectOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBASelectOperator>();
}

}

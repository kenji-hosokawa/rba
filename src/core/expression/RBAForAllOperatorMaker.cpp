
/// @file  RBAForAllOperatorMaker.cpp
/// @brief ForAllOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAForAllOperatorMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBAForAllOperator.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBAForAllOperatorMaker::RBAForAllOperatorMaker()
  : RBALambdaContextMaker{"ForAllOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAForAllOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAForAllOperator>();
}

RBAModelElement*
RBAForAllOperatorMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBAForAllOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBAForAllOperator>();
}

}

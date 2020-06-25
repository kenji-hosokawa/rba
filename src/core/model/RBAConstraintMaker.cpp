/// @file  RBAConstraintMaker.cpp
/// @brief 制約式オブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAConstraintMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAConstraintMaker::RBAConstraintMaker()
  : RBAAbstractConstraintMaker{"constraints"}
{
}

std::unique_ptr<RBAModelElement>
RBAConstraintMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAConstraintImpl>(name);
}

RBAModelElement*
RBAConstraintMaker::setProperty(RBAModelElement* element,
                                const RBAJsonElement* jsonElem,
                                RBAModelImpl* model,
                                RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractConstraintMaker::setProperty(element, jsonElem, model, owner));

  const auto constraint = dynamic_cast<RBAConstraintImpl*>(element);

  // Set runtime
  bool runtime {false};
  if(jsonElem->findChildren("runtime")->getString() == "true") {
    runtime = true;
  }
  constraint->setRuntime(runtime);

  model->addConstraint(constraint);

  return constraint;
}

}

/// @file  RBAObjectReferenceMaker.cpp
/// @brief ObjectReferenceオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAObjectReferenceMaker.hpp"
#include "RBAObjectReference.hpp"

#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"

namespace rba
{

RBAObjectReferenceMaker::RBAObjectReferenceMaker(const std::string& label)
  : RBAExpressionMaker{label}
{
}

std::unique_ptr<RBAModelElement>
RBAObjectReferenceMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAObjectReference>();
}

RBAModelElement*
RBAObjectReferenceMaker::setProperty(RBAModelElement* element,
                                     const RBAJsonElement* jsonElem,
                                     RBAModelImpl* model,
                                     RBAModelElement* owner)
{
  RBAObjectReference* const objRef {dynamic_cast<RBAObjectReference*>(element)};

  // Set reference object
  //// Getting reference object string
  const auto& refObjectStr = jsonElem->findChildren("refObject")->getString();

  //// Find object
  auto ruleObj = model->findModelElement(refObjectStr);

  if(ruleObj == nullptr) {
    ruleObj = getFactory()->getVariable(refObjectStr);
    if(ruleObj == nullptr) {
      const auto& typeStr = jsonElem->findChildren("type")->getString();
      auto maker = getMaker(typeStr);
      if (maker != nullptr) {
        ruleObj = maker->getInstance(model, refObjectStr, owner);
      }
    }
  }
  objRef->setRefObject(dynamic_cast<const RBARuleObject*>(ruleObj));

#ifdef RBA_USE_LOG
  // Set expression type
  const RBAExpressionType exprType {jsonElem->getExpressionType()};
  objRef->setExpressionType(exprType);
#endif

  return objRef;
}

}

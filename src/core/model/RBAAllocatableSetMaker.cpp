/// @file  RBAAllocatableSetMaker.cpp
/// @brief AllocatableSetオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllocatableSetMaker.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllocatableSetMaker::RBAAllocatableSetMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractAllocatableMaker{label}
{
}

RBAModelElement*
RBAAllocatableSetMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractAllocatableMaker::setProperty(element, jsonElem, model, owner));

  const auto allocSet = dynamic_cast<RBAAllocatableSet*>(element);

  // Set target
  const RBAJsonElement* const target {jsonElem->findChildren("target")};
  for(const auto& targetElem : target->getChildren()) {
    const auto alloc = model->findAllocatable(targetElem->getName());
    allocSet->addTarget(alloc);
  }

  return allocSet;
}

}

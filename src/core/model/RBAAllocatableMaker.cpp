/// @file  RBAAllocatableMaker.cpp
/// @brief Allocatableオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllocatableMaker.hpp"
#include "RBAAllocatable.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllocatableMaker::RBAAllocatableMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractAllocatableMaker{label}
{
}

RBAModelElement*
RBAAllocatableMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractAllocatableMaker::setProperty(element, jsonElem, model, owner));

  const auto alloc = dynamic_cast<RBAAllocatable*>(element);

  // Set policy
  const RBAJsonElement* const policy {jsonElem->findChildren("arbitrationPolicy")};
  if(policy == nullptr) {
    std::cerr << alloc->getElementName()
              << ": arbitrationPolicy not found" << &std::endl;
    return nullptr;
  }
  alloc->setArbitrationPolicy(policy->getArbitrationPolicy());

  // Set visibility or priority
  if (alloc->isArea()) {
    const RBAJsonElement* const visibility {jsonElem->findChildren("visibility")};
    if(visibility == nullptr) {
    	std::cerr << alloc->getElementName()
                << ": visibility not found" << &std::endl;
      return nullptr;
    }
    alloc->setVisibility(visibility->getInt());
  } else if (alloc->isZone()) {
    const RBAJsonElement* const priority {jsonElem->findChildren("priority")};
    if(priority == nullptr) {
      std::cerr << alloc->getElementName()
                << ": priority not found" << &std::endl;
      return nullptr;
    }
    alloc->setVisibility(priority->getInt());
  } else {
    ;
  }

  model->addAllocatable(alloc);

  return alloc;
}

}

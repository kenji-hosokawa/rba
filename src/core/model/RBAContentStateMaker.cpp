/// @file  RBAContentStateMaker.cpp
/// @brief ContentStateオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAContentStateMaker.hpp"
#include "RBAContentState.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAContentStateMaker::RBAContentStateMaker(const std::string& label)
  : RBARuleObjectMaker{label}
{
}

RBAModelElement*
RBAContentStateMaker::getInstance(RBAModelImpl* model,
                                  const std::string& name,
                                  RBAModelElement* owner)
{
  RBAModelElement* ret {nullptr};

  const auto content = dynamic_cast<RBAContent*>(owner);
  const auto uniqueName = content->getUniqueName() + "/" + name;

  const auto element = model->findModelElement(uniqueName);
  // modelに存在する場合
  if(element != nullptr) {
    ret = const_cast<RBAModelElement*>(element);
  }
  // modelに存在しない場合
  else {
    std::unique_ptr<RBAModelElement> inst {createInstance(name)};
    const auto contentState = dynamic_cast<RBAContentState*>(inst.get());
    contentState->setOwner(content);
    ret =  model->addNamedElement(std::move(inst));
  }

  return ret;
}

RBAModelElement*
RBAContentStateMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));

  RBAContentState* const state {dynamic_cast<RBAContentState*>(element)};

  // Set priority
  state->setPriority(jsonElem->findChildren("priority")->getInt());

  model->addContentState(state);

  return state;
}

}

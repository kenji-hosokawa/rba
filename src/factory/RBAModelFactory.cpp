/// @file  RBAModelFactory.cpp
/// @brief モデルファクトリクラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <algorithm>
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAAbstractMakerTable.hpp"
#include "RBAConstraintImpl.hpp"

namespace rba
{

RBAModelFactory::RBAModelFactory(RBAModelImpl* const model)
  : model_{nullptr},
    exception_{false}
{
  if(model != nullptr) {
    model_ = model;
  }
  else {
    // @Deviation (A18-5-2)
    // 【ルールに逸脱している内容】
    //  Operators new and delete shall not be called explicitly.
    // 【ルールを逸脱しても問題ないことの説明】
    //  model_ は RBAModelFacotry が所有しない。そのためスマートポインタでは管理しない。 RBAModelFactory の使用側で管理されているので問題ない。
    model_ = new RBAModelImpl();
  }
}

RBAModelFactory::~RBAModelFactory() noexcept
{
}

RBAModel* const
RBAModelFactory::getModel() const
{
  return model_;
}

void
RBAModelFactory::deleteModel()
{
    // @Deviation (A18-5-2)
    // 【ルールに逸脱している内容】
    //  Operators new and delete shall not be called explicitly.
    // 【ルールを逸脱しても問題ないことの説明】
    //  RBAModelFactory の使用側で管理されているので、外部から delete されても問題ない。
  delete model_;
  model_ = nullptr;
}

void
RBAModelFactory::addMakerTable(const RBAAbstractMakerTable& makerTable)
{
  for(auto& maker : makerTable.getMakers()) {
    maker->setFactory(this);
    const std::string label {maker->getLabel()};
    nameToMaker_[label] = maker.get();
    makers_.push_back(std::move(maker));
  }
  for(auto& tag : makerTable.getTags()) {
    if (std::find(tags_.begin(), tags_.end(), tag) == tags_.end()) {
      tags_.push_back(tag);
    }
  }
}

void
RBAModelFactory::addMaker(const std::string label,
                          std::unique_ptr<RBAModelElementMaker> maker)
{
  maker->setFactory(this);
  nameToMaker_[label] = maker.get();
  makers_.push_back(std::move(maker));
}

bool
RBAModelFactory::hasMaker() const
{
  return !nameToMaker_.empty();
}

const std::list<std::string>&
RBAModelFactory::getTags() const
{
  return tags_;
}

RBAModelElement*
RBAModelFactory::createElement(const std::string& className,
                               const RBAJsonElement* const jsonElement,
                               RBAModelElement* const owner)
{
  auto it = nameToMaker_.find(className);
  if(it == nameToMaker_.end()) {
    const RBAJsonElement* const classElement {jsonElement->findChildren("class")};
    if(classElement != nullptr) {
      it = nameToMaker_.find(classElement->getString());
      if(it == nameToMaker_.end()) {
        return nullptr;
      }
    }
    else {
      return nullptr;
    }
  }

  return it->second->create(jsonElement, model_, owner);
}

void
RBAModelFactory::setAllocatableConstraint(const std::string& allocatableName,
                                          const std::string& constraintName,
                                          const RBAConstraintMap& kind)
{
  // アロケータブルを取得
  RBAAllocatable* const allocatable
    {const_cast<RBAAllocatable*>(model_->findAllocatable(allocatableName))};
  // 制約式を取得
  RBAConstraintImpl* const constraint {model_->findConstraintImpl(constraintName)};
  if ((allocatable != nullptr) && (constraint != nullptr)) {
    allocatable->addConstraint(constraint, kind);
  }
}

// Variableは異なるスコープで同じ名前のものが定義できるが、ここで今生成中のスコープで定義されている
// Variableを登録している
void
RBAModelFactory::pushVariable(const RBAVariable* const var)
{
  currentVariables_.push_back(var);
}

// Variableは異なるスコープで同じ名前のものが定義できるが、定義のあるスコープから抜けた時、
// Variableを削除している。
void
RBAModelFactory::popVariable()
{
  if(!currentVariables_.empty()) {
    currentVariables_.pop_back();
  }
}

const RBAVariable*
RBAModelFactory::getVariable(const std::string& varName)
{
  const auto itr =
      std::find_if(currentVariables_.rbegin(), currentVariables_.rend(),
                   [&varName](const RBAVariable* element) -> bool {
                     return element->getElementName() == varName;
                   });

  if (itr != currentVariables_.rend())
  {
    return *itr;
  }

  return nullptr;
}

void
RBAModelFactory::resetException()
{
  exception_ = false;
}

void
RBAModelFactory::setException()
{
  exception_ = true;
}

bool
RBAModelFactory::isException() const
{
  return exception_;
}

}

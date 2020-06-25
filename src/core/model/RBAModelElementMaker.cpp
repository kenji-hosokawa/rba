/// @file  RBAModelElementMaker.cpp
/// @brief モデルオブジェクト生成の抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAModelElementMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"

namespace rba
{

std::unordered_map<std::string, std::unique_ptr<RBAModelElementMaker>> RBAModelElementMaker::makerMap_;

RBAModelElementMaker::RBAModelElementMaker(const std::string& label)
  : factory_{nullptr},
    label_{label}
{
}

void
RBAModelElementMaker::setFactory(RBAModelFactory* const factory)
{
  factory_ = factory;
}

RBAModelFactory* RBAModelElementMaker::getFactory() const
{
  return factory_;
}

const std::string&
RBAModelElementMaker::getLabel() const
{
  return label_;
}

RBAModelElement*
RBAModelElementMaker::create(const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  const auto nameElement = jsonElem->findChildren("name");

  RBAModelElement* element {nullptr};
  if (nameElement != nullptr) {
    element = getInstance(model, nameElement->getString(), owner);
  } else {
    element = getInstance(model, "", owner);
  }

  return setProperty(element, jsonElem, model, owner);
}

RBAModelElement*
RBAModelElementMaker::getInstance(RBAModelImpl* model,
                                  const std::string& name,
                                  RBAModelElement* owner)
{
  RBAModelElement* ret {nullptr};

  // クラス名付きの場合はクラス名を消す
  std::string fullName {name};
  while (fullName.find(':') != std::string::npos) {
    const auto start = fullName.find(':');
    const auto end = fullName.find('/', start);
    static_cast<void>(fullName.erase(start, end - start));
  }

  // 名前ありエレメントの場合
  if(fullName != "") {
    const auto elem = model->findModelElement(fullName);
    // modelに存在する場合
    if(elem != nullptr) {
      ret = const_cast<RBAModelElement*>(elem);
    }
    // modelに存在しない場合
    else {
      std::unique_ptr<RBAModelElement> inst {createInstance(fullName)};
      ret = model->addNamedElement(std::move(inst));
    }
  }
  // 名前なしエレメントの場合
  else {
    std::unique_ptr<RBAModelElement> inst {createInstance()};
    ret = model->addModelElement(std::move(inst));
  }
  
  return ret;
}

void
RBAModelElementMaker::addMaker(const std::string& typeName, std::unique_ptr<RBAModelElementMaker> maker)
{
  makerMap_[typeName] = std::move(maker);
}

RBAModelElementMaker*
RBAModelElementMaker::getMaker(const std::string& typeName)
{
  if (makerMap_.find(typeName) == makerMap_.end()) {
    return nullptr;
  }
  return makerMap_[typeName].get();
}

}

/// @file  RBAJsonParserImpl.cpp
/// @brief JSONパーサー実装クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <fstream>
#include <sstream>
#include <iostream>
#include "RBAJsonParserImpl.hpp"

#include "RBACommonMakerTable.hpp"
#include "RBAConstraintMap.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASoundMakerTable.hpp"
#include "RBAViewMakerTable.hpp"

namespace rba
{

RBAJsonParser::Impl::
Impl(RBAModelFactory* const factory)
  :   orgFactory_{factory},
      factory_{nullptr}
{
}

RBAModel*
RBAJsonParser::Impl::
parse(const std::string& filename)
{
  const std::unique_ptr<RBAJsonElement> root {readJsonFile(filename)};
  if(root == nullptr) {
    return nullptr;
  }

  const std::lock_guard<std::mutex> lock{mutex_};

  if(orgFactory_ != nullptr) {
    factory_ = orgFactory_;
  }
  else {
    uniqueFactory_ = std::make_unique<RBAModelFactory>();
    factory_ = uniqueFactory_.get();
  }
  resetFactory();

  // 登録されたタグの要素を取り出す
  for(const auto& tag : factory_->getTags()) {
    const RBAJsonElement* const jsonElems {root->findChildren(tag)};
    if(jsonElems != nullptr) {
      for(const auto& elem : jsonElems->getChildren()) {
        // モデルエレメントを生成
        const RBAModelElement* const modelElem {factory_->createElement(tag, elem.get())};
        if(modelElem == nullptr) {
          factory_->deleteModel();
          return nullptr;
        }
      }
    }
  }

  // Factoryで例外があればエラー
  if(factory_->isException()) {
    factory_->deleteModel();
    return nullptr;
  }

  // エリアと制約式のマップを作成
  createConstraintMap(root->findChildren("area_constraint_map"),
                      RBAConstraintMap::CONTENT_ALLOCATE_CONSTRAINTS);
  createConstraintMap(root->findChildren("area_hidden_true_check_constraint_map"),
                      RBAConstraintMap::HIDDEN_TRUE_CHECK_CONSTRAINTS);
  createConstraintMap(root->findChildren("area_hidden_false_check_constraint_map"),
                      RBAConstraintMap::HIDDEN_FALSE_CHECK_CONSTRAINTS);

  // ゾーンと制約式のマップを作成
  createConstraintMap(root->findChildren("zone_constraint_map"),
                      RBAConstraintMap::CONTENT_ALLOCATE_CONSTRAINTS);
  createConstraintMap(root->findChildren("zone_mute_true_check_constraint_map"),
                      RBAConstraintMap::HIDDEN_TRUE_CHECK_CONSTRAINTS);
  createConstraintMap(root->findChildren("zone_mute_false_check_constraint_map"),
                      RBAConstraintMap::HIDDEN_FALSE_CHECK_CONSTRAINTS);
  createConstraintMap(root->findChildren("zone_attenuate_true_check_constraint_map"),
                      RBAConstraintMap::ATTENUATE_TRUE_CHECK_CONSTRAINTS);
  createConstraintMap(root->findChildren("zone_attenuate_false_check_constraint_map"),
                      RBAConstraintMap::ATTENUATE_FALSE_CHECK_CONSTRAINTS);

  // 影響するアロケータブルマップの作成
//  createAllocatablesMap(root->findChildren("content_allocatables_map"));
//  createAllocatablesMap(root->findChildren("scene_allocatables_map"));
//  createAllocatablesMap(root->findChildren("statemachine_allocatables_map"));

  // コンテンツがなければエラー
  if((factory_->getModel()->getViewContents().size() == 0U) &&
     (factory_->getModel()->getSoundContents().size() == 0U)) {
    std::cerr << filename << ": ViewContent or SoundContent not found"
              << &std::endl;
    factory_->deleteModel();
    return nullptr;
  }

  return factory_->getModel();
}

void
RBAJsonParser::Impl::createConstraintMap(const RBAJsonElement* const constraints,
                                         const RBAConstraintMap& kind)
{
  if (constraints != nullptr) {
    for (const auto& constraint : constraints->getChildren()) {
      const RBAJsonElement* const elem {constraint->getChildren().front().get()};
      const std::string& allocatableName {elem->getName()};
      for (auto& e : elem->getChildren()) {
        factory_->setAllocatableConstraint(allocatableName, e->getName(), kind);
      }
    }
  }
}

void
RBAJsonParser::Impl::createAllocatablesMap(const RBAJsonElement* const allocMap)
{
  if (allocMap != nullptr) {
    RBAModelImpl* const model {dynamic_cast<RBAModelImpl*>(factory_->getModel())};    
    for (auto& elem : allocMap->getChildren()) {      
      // 影響元オブジェクト取得
      const auto owner = elem->getChild();
      const auto ownerObj = model->findModelElementImpl(owner->getName());
      
      for (auto& alloc : owner->getChildren()) {
        // 影響先アロケータブル取得
        const auto allocObj = model->findAllocatable(alloc->getName());
        
        // マップへ追加
        model->addAffectedAllocsMap(ownerObj, const_cast<RBAAllocatable*>(allocObj));
      }
    }
  }
}

std::unique_ptr<RBAJsonElement>
RBAJsonParser::Impl::readJsonFile(const std::string& filename)
{
  std::ifstream ifs{filename};
  if(ifs.fail()) {
    std::cerr << filename << ": No such file or directory" << &std::endl;
    return nullptr;
  }

  std::ostringstream oss;
  std::string line;
  while(!ifs.eof()) {
    ifs >> line;
    oss << line;
  }

  return readJsonString(oss.str());
}

std::unique_ptr<RBAJsonElement>
RBAJsonParser::Impl::readJsonString(const std::string& jsonstring)
{
  std::vector<RBAJsonElement*> queue;
  RBAJsonElement* current{nullptr};
  std::unique_ptr<RBAJsonElement> topElement{nullptr};
  Status status{Status::START};
  const std::size_t jsonSize{jsonstring.size()};
  std::size_t tokenPos{0U};
  std::size_t tokenSize{0U};
  std::size_t strPos{0U};
  std::size_t strSize{0U};

  while (tokenPos < jsonSize) {
    auto firstChar = jsonstring[tokenPos];
    if(firstChar == '\"') {
      // 文字列
      tokenSize = jsonstring.find('\"', tokenPos + 1U) - tokenPos + 1U;
      switch(status) {
      case Status::START:
        strPos = tokenPos + 1U;
        strSize = tokenSize - 2U;
        break;
      case Status::VALUE:
        auto elem = std::make_unique<RBAJsonElementString>(jsonstring.substr(strPos, strSize));
        elem->setString(jsonstring.substr(tokenPos + 1U, tokenSize - 2U));
        current->addChild(std::move(elem));
        strSize = 0U;
        status = Status::START;
        break;
      }
    }
    else if(firstChar == ':') {
      // 値モード
      tokenSize = 1U;
      status = Status::VALUE;
    }
    else if(firstChar == ',') {
      tokenSize = 1U;
      if(strSize > 0U) {
	      current->addChild(std::make_unique<RBAJsonElementString>(jsonstring.substr(strPos, strSize)));
        strSize = 0U;
        status = Status::START;
      }
    }
    else if(firstChar == '{') {
      // Element開始
      tokenSize = 1U;
      if(status == Status::START) {
        if(current != nullptr) {
          auto elem = std::make_unique<RBAJsonElementElement>(jsonstring.substr(strPos, strSize));
          auto elemPtr = elem.get();
          current->addChild(std::move(elem));
          current = elemPtr;
          queue.push_back(current);
          strSize = 0U;
        }
      } else {
        // status は Status::VALUE
        auto elem = std::make_unique<RBAJsonElementElement>(jsonstring.substr(strPos, strSize));
        auto elemPtr = elem.get();
        if(current != nullptr) {
          current->addChild(std::move(elem));
        } else {
          topElement = std::move(elem);
        }
        current = elemPtr;
        queue.push_back(current);
        strSize = 0U;
        status = Status::START;
      }
    }
    else if(firstChar == '}') {
      // Element終了
      tokenSize = 1U;
      if (!queue.empty()) {
        queue.pop_back();
      }
      current = queue.empty() ? nullptr : queue.back();
    }
    else if(firstChar == '[') {
      // 配列開始
      tokenSize = 1U;
      auto elem = std::make_unique<RBAJsonElementArray>(jsonstring.substr(strPos, strSize));
      auto elemPtr = elem.get();
      current->addChild(std::move(elem));
      current = elemPtr;
      queue.push_back(current);
      strSize = 0U;
      status = Status::START;
    }
    else if(firstChar == ']') {
      // 配列終了
      tokenSize = 1U;
      if(strSize > 0U) {
        current->addChild(std::make_unique<RBAJsonElementString>(jsonstring.substr(strPos, strSize)));
        strSize = 0U;
        status = Status::START;
      }
      queue.pop_back();
      current = queue.empty() ? nullptr : queue.back();
    }
    else if((firstChar == '-') || isdigit(firstChar)) {
      // 数値
      tokenSize = jsonstring.find_first_of(",}]", tokenPos + 1U) - tokenPos;
      auto elem = std::make_unique<RBAJsonElementInt>(jsonstring.substr(strPos, strSize));
      elem->setInt(std::stoi(jsonstring.substr(tokenPos, tokenSize)));
      current->addChild(std::move(elem));
      strSize = 0U;
      status = Status::START;
    }
    else if((static_cast<std::int32_t>(firstChar) <= 0x20)) {
      // skip
      tokenSize = 1U;
    }
    else {
      tokenSize = 1U;
      std::cerr << "[ERROR] '" << jsonstring.substr(tokenPos, tokenSize)
       << "' :Unknown token" << &std::endl;
    }
    tokenPos += tokenSize;
  }

  return topElement;
}

void
RBAJsonParser::Impl::resetFactory()
{
  // Makerが未登録ならセット
  if(!factory_->hasMaker()) {
    // area, zoneなどのモデルを先に登録すること。
    factory_->addMakerTable(RBAViewMakerTable());
    factory_->addMakerTable(RBASoundMakerTable());
    factory_->addMakerTable(RBACommonMakerTable());
  }

  // ファクトリの初期化
  factory_->resetException();
}

}

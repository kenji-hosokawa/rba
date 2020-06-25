/// @file  RBAViewMakerTable.cpp
/// @brief ビューエレメントメーカーテーブルクラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAViewMakerTable.hpp"
#include "RBAAllInstanceOfAreaMaker.hpp"
#include "RBAAllInstanceOfViewContentMaker.hpp"
#include "RBAAreaMaker.hpp"
#include "RBAAreaSetMaker.hpp"
#include "RBADisplayMaker.hpp"
#include "RBADisplayingContentMaker.hpp"
#include "RBAIsDisplayedMaker.hpp"
#include "RBAIsHiddenMaker.hpp"
#include "RBAIsVisibleMaker.hpp"
#include "RBAPositionContainerMaker.hpp"
#include "RBASizeMaker.hpp"
#include "RBAViewContentMaker.hpp"
#include "RBAViewContentSetMaker.hpp"
#include "RBAViewContentStateMaker.hpp"

namespace rba
{

RBAViewMakerTable::RBAViewMakerTable()
  : RBAAbstractMakerTable{}
{
  addTag("areas");
  addTag("areasets");
  addTag("viewcontents");
  addTag("viewcontentsets");
  addTag("displays");
}

std::list<std::unique_ptr<RBAModelElementMaker>>
RBAViewMakerTable::getMakers() const
{
  std::list<std::unique_ptr<RBAModelElementMaker>> makers;
  makers.push_back(std::make_unique<RBAAllInstanceOfAreaMaker>());
  makers.push_back(std::make_unique<RBAAllInstanceOfViewContentMaker>());
  makers.push_back(std::make_unique<RBAAreaMaker>());
  RBAModelElementMaker::addMaker("AREA", std::make_unique<RBAAreaMaker>());
  makers.push_back(std::make_unique<RBAAreaSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_AREA", std::make_unique<RBAAreaSetMaker>());
  makers.push_back(std::make_unique<RBADisplayMaker>());
  makers.push_back(std::make_unique<RBADisplayingContentMaker>());
  makers.push_back(std::make_unique<RBAIsDisplayedMaker>());
  makers.push_back(std::make_unique<RBAIsHiddenMaker>());
  makers.push_back(std::make_unique<RBAIsVisibleMaker>());
  makers.push_back(std::make_unique<RBAPositionContainerMaker>());
  makers.push_back(std::make_unique<RBASizeMaker>());
  makers.push_back(std::make_unique<RBAViewContentMaker>());
  RBAModelElementMaker::addMaker("CONTENT", std::make_unique<RBAViewContentMaker>());
  RBAModelElementMaker::addMaker("ViewContent", std::make_unique<RBAViewContentMaker>());
  makers.push_back(std::make_unique<RBAViewContentSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_CONTENT", std::make_unique<RBAViewContentSetMaker>());
  makers.push_back(std::make_unique<RBAViewContentStateMaker>());

  return makers;
}

}

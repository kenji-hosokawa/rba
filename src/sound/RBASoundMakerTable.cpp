/// @file  RBASoundMakerTable.cpp
/// @brief 音声エレメントメーカーテーブルクラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASoundMakerTable.hpp"
#include "RBAAllInstanceOfSoundContentMaker.hpp"
#include "RBAAllInstanceOfZoneMaker.hpp"
#include "RBAIsAttenuatedMaker.hpp"
#include "RBAIsMutedMaker.hpp"
#include "RBAIsOutputtedMaker.hpp"
#include "RBAIsSoundingMaker.hpp"
#include "RBAOutputtingSoundMaker.hpp"
#include "RBASoundContentMaker.hpp"
#include "RBASoundContentSetMaker.hpp"
#include "RBASoundContentStateMaker.hpp"
#include "RBAZoneMaker.hpp"
#include "RBAZoneSetMaker.hpp"

namespace rba
{

RBASoundMakerTable::RBASoundMakerTable()
  : RBAAbstractMakerTable{}
{
  addTag("zones");
  addTag("zonesets");
  addTag("soundcontents");
  addTag("soundcontentsets");
}

std::list<std::unique_ptr<RBAModelElementMaker>>
RBASoundMakerTable::getMakers() const
{
  std::list<std::unique_ptr<RBAModelElementMaker>> makers;
  makers.push_back(std::make_unique<RBAAllInstanceOfSoundContentMaker>());
  makers.push_back(std::make_unique<RBAAllInstanceOfZoneMaker>());
  makers.push_back(std::make_unique<RBAIsAttenuatedMaker>());
  makers.push_back(std::make_unique<RBAIsMutedMaker>());
  makers.push_back(std::make_unique<RBAIsOutputtedMaker>());
  makers.push_back(std::make_unique<RBAIsSoundingMaker>());
  makers.push_back(std::make_unique<RBAOutputtingSoundMaker>());
  makers.push_back(std::make_unique<RBASoundContentMaker>());
  RBAModelElementMaker::addMaker("SOUND", std::make_unique<RBASoundContentMaker>());
  RBAModelElementMaker::addMaker("SoundContent", std::make_unique<RBASoundContentMaker>());
  makers.push_back(std::make_unique<RBASoundContentSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_SOUND", std::make_unique<RBASoundContentSetMaker>());
  makers.push_back(std::make_unique<RBASoundContentStateMaker>());
  makers.push_back(std::make_unique<RBAZoneMaker>());
  RBAModelElementMaker::addMaker("ZONE", std::make_unique<RBAZoneMaker>());
  makers.push_back(std::make_unique<RBAZoneSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_ZONE", std::make_unique<RBAZoneSetMaker>());

  return makers;
}

}

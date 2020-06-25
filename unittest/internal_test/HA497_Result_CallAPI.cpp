// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Result_CallAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Result_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Result_CallAPI::HA497_Result_CallAPI(void)
{
}

HA497_Result_CallAPI::~HA497_Result_CallAPI(void)
{
}

void HA497_Result_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Result_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_Result_CallAPI, getSoundingZones) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getSoundingZones();
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"SoundA1");
  allocatables = result->getSoundingZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getSoundingZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // MutedとAttenatedの場合
  result = arb->execute(u8"SoundB1");
  result = arb->execute(u8"SoundC1");
  allocatables = result->getSoundingZones();
  ASSERT_EQ(allocatables.size(), 2U);
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneA")),allocatables.end());
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneC")),allocatables.end());
}
TEST_F(HA497_Result_CallAPI, getVisibleContentStates) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAViewContentState*> contentStates;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  contentStates = result->getVisibleContentStates();
  EXPECT_EQ(contentStates.size(), 0U);
  result = arb->execute(u8"ViewA1");
  contentStates = result->getVisibleContentStates();
  ASSERT_EQ(contentStates.size(), 1U);
  EXPECT_EQ(contentStates.front(),model->findViewContentState(u8"ViewA1"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  contentStates = result->getVisibleContentStates();
  ASSERT_EQ(contentStates.size(), 1U);
  EXPECT_EQ(contentStates.front(),model->findViewContentState(u8"ViewA1"));
  // MutedとAttenatedの場合
  result = arb->execute(u8"ViewB1");
  result = arb->execute(u8"ViewC1");
  contentStates = result->getVisibleContentStates();
  ASSERT_EQ(contentStates.size(), 2U);
  EXPECT_NE(std::find(contentStates.begin(),contentStates.end(),model->findViewContentState(u8"ViewA1")),contentStates.end());
  EXPECT_NE(std::find(contentStates.begin(),contentStates.end(),model->findViewContentState(u8"ViewC1")),contentStates.end());
}
TEST_F(HA497_Result_CallAPI, getSoundingContentStates) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBASoundContentState*> contentStates;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  contentStates = result->getSoundingContentStates();
  EXPECT_EQ(contentStates.size(), 0U);
  result = arb->execute(u8"SoundA1");
  contentStates = result->getSoundingContentStates();
  ASSERT_EQ(contentStates.size(), 1U);
  EXPECT_EQ(contentStates.front(),model->findSoundContentState(u8"SoundA1"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  contentStates = result->getSoundingContentStates();
  ASSERT_EQ(contentStates.size(), 1U);
  EXPECT_EQ(contentStates.front(),model->findSoundContentState(u8"SoundA1"));
  // MutedとAttenatedの場合
  result = arb->execute(u8"SoundB1");
  result = arb->execute(u8"SoundC1");
  contentStates = result->getSoundingContentStates();
  ASSERT_EQ(contentStates.size(), 2U);
  EXPECT_NE(std::find(contentStates.begin(),contentStates.end(),model->findSoundContentState(u8"SoundA1")),contentStates.end());
  EXPECT_NE(std::find(contentStates.begin(),contentStates.end(),model->findSoundContentState(u8"SoundC1")),contentStates.end());
}
TEST_F(HA497_Result_CallAPI, getUnsoundingZones) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getUnsoundingZones();
  ASSERT_EQ(allocatables.size(), 3U);
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneA")),allocatables.end());
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneB")),allocatables.end());
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneC")),allocatables.end());
  result = arb->execute(u8"SoundA1");
  allocatables = result->getUnsoundingZones();
  ASSERT_EQ(allocatables.size(), 2U);
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneB")),allocatables.end());
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneC")),allocatables.end());
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getUnsoundingZones();
  ASSERT_EQ(allocatables.size(), 2U);
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneB")),allocatables.end());
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneC")),allocatables.end());
  // MutedとAttenatedの場合
  result = arb->execute(u8"SoundB1");
  result = arb->execute(u8"SoundC1");
  allocatables = result->getUnsoundingZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
}
TEST_F(HA497_Result_CallAPI, getHiddenAreas) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAArea*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getHiddenAreas();
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"ViewB1");
  allocatables = result->getHiddenAreas();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaB"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getHiddenAreas();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaB"));
  // 通常出力の場合
  result = arb->execute(u8"ViewA1");
  result = arb->execute(u8"ViewC1");
  allocatables = result->getHiddenAreas();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaB"));
}
TEST_F(HA497_Result_CallAPI, getMuteZones) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getMuteZones();
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"SoundB1");
  allocatables = result->getMuteZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getMuteZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
  // 通常出力とAttenatedの場合
  result = arb->execute(u8"SoundA1");
  result = arb->execute(u8"SoundC1");
  allocatables = result->getMuteZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
}
TEST_F(HA497_Result_CallAPI, getAttenuatedZones) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getAttenuatedZones();
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"SoundC1");
  allocatables = result->getAttenuatedZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneC"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getAttenuatedZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneC"));
  // MutedとAttenatedの場合
  result = arb->execute(u8"SoundA1");
  result = arb->execute(u8"SoundB1");
  allocatables = result->getAttenuatedZones();
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_NE(std::find(allocatables.begin(),allocatables.end(),model->findZone(u8"ZoneC")),allocatables.end());
}
TEST_F(HA497_Result_CallAPI, getStandbyViewContents) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAViewContent*> contents;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  contents = result->getStandbyViewContents();
  EXPECT_EQ(contents.size(), 0U);
  result = arb->execute(u8"ViewA2");
  contents = result->getStandbyViewContents();
  EXPECT_EQ(contents.size(), 0U);
  result = arb->execute(u8"ViewA1");
  contents = result->getStandbyViewContents();
  ASSERT_EQ(contents.size(), 1U);
  EXPECT_EQ(contents.front(),model->findViewContent(u8"ViewA2"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  contents = result->getStandbyViewContents();
  EXPECT_EQ(contents.size(), 1U);
  EXPECT_EQ(contents.front(),model->findViewContent(u8"ViewA2"));
}
TEST_F(HA497_Result_CallAPI, getStandbySoundContents) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBASoundContent*> contents;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  contents = result->getStandbySoundContents();
  EXPECT_EQ(contents.size(), 0U);
  result = arb->execute(u8"SoundA2");
  contents = result->getStandbySoundContents();
  EXPECT_EQ(contents.size(), 0U);
  result = arb->execute(u8"SoundA1");
  contents = result->getStandbySoundContents();
  ASSERT_EQ(contents.size(), 1U);
  EXPECT_EQ(contents.front(),model->findSoundContent(u8"SoundA2"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  contents = result->getStandbySoundContents();
  EXPECT_EQ(contents.size(), 1U);
  EXPECT_EQ(contents.front(),model->findSoundContent(u8"SoundA2"));
}
TEST_F(HA497_Result_CallAPI, getArea_ViewContentState) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAArea*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getArea(model->findViewContentState(u8"ViewA1"));
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"ViewA1");
  allocatables = result->getArea(model->findViewContentState(u8"ViewA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaA"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getArea(model->findViewContentState(u8"ViewA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaA"));
  // Mutedの場合
  result = arb->execute(u8"ViewB1");
  allocatables = result->getArea(model->findViewContentState(u8"ViewB1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaB"));
  // Attenuatedの場合
  result = arb->execute(u8"ViewC1");
  allocatables = result->getArea(model->findViewContentState(u8"ViewC1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaC"));
}
TEST_F(HA497_Result_CallAPI, getZone_SoundContentState) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getZone(model->findSoundContentState(u8"SoundA1"));
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"SoundA1");
  allocatables = result->getZone(model->findSoundContentState(u8"SoundA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getZone(model->findSoundContentState(u8"SoundA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // Mutedの場合
  result = arb->execute(u8"SoundB1");
  allocatables = result->getZone(model->findSoundContentState(u8"SoundB1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
  // Attenuatedの場合
  result = arb->execute(u8"SoundC1");
  allocatables = result->getZone(model->findSoundContentState(u8"SoundC1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneC"));
}
TEST_F(HA497_Result_CallAPI, getArea_ViewContent) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAArea*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getArea(model->findViewContent(u8"ViewA1"));
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"ViewA1");
  allocatables = result->getArea(model->findViewContent(u8"ViewA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaA"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getArea(model->findViewContent(u8"ViewA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaA"));
  // Mutedの場合
  result = arb->execute(u8"ViewB1");
  allocatables = result->getArea(model->findViewContent(u8"ViewB1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaB"));
  // Attenuatedの場合
  result = arb->execute(u8"ViewC1");
  allocatables = result->getArea(model->findViewContent(u8"ViewC1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findArea(u8"AreaC"));
}
TEST_F(HA497_Result_CallAPI, getZone_SoundContent) {
  std::unique_ptr<RBAResult> result;
  std::list<const RBAZone*> allocatables;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  allocatables = result->getZone(model->findSoundContent(u8"SoundA1"));
  EXPECT_EQ(allocatables.size(), 0U);
  result = arb->execute(u8"SoundA1");
  allocatables = result->getZone(model->findSoundContent(u8"SoundA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // 表示状態が変化しなければ、取得できる値も変化しないことの確認
  result = arb->execute();
  allocatables = result->getZone(model->findSoundContent(u8"SoundA1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneA"));
  // Mutedの場合
  result = arb->execute(u8"SoundB1");
  allocatables = result->getZone(model->findSoundContent(u8"SoundB1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneB"));
  // Attenuatedの場合
  result = arb->execute(u8"SoundC1");
  allocatables = result->getZone(model->findSoundContent(u8"SoundC1"));
  ASSERT_EQ(allocatables.size(), 1U);
  EXPECT_EQ(allocatables.front(),model->findZone(u8"ZoneC"));
}
}

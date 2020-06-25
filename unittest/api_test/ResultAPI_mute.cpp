// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_muted.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_mute.hpp"

namespace resultapi {

using namespace rba;

/*
 * muteテスト
 */
ResultAPI_mute::ResultAPI_mute()
{
  jsonFile = JSONFILE_ALLOCATABLE_CONTENT;
}

ResultAPI_mute::~ResultAPI_mute()
{
}

/**************************************************
 * Attenuatedなし
 **************************************************/

// １つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_001_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_002_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_003_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_004_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンにコンテントの割り当てなし + mute
TEST_F(ResultAPI_mute, tc_005_mute_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1) + mute
TEST_F(ResultAPI_mute, tc_006_mute_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2) + mute
TEST_F(ResultAPI_mute, tc_007_mute_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2) + mute
TEST_F(ResultAPI_mute, tc_008_mute_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_009_2zone)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_010_2zone_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_011_2zone_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_012_2zone_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneB"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneB"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA
TEST_F(ResultAPI_mute, tc_013_2zone_muteA)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA
TEST_F(ResultAPI_mute, tc_014_2zone_muteA_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA
TEST_F(ResultAPI_mute, tc_015_2zone_muteA_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA
TEST_F(ResultAPI_mute, tc_016_2zone_muteA_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteB
TEST_F(ResultAPI_mute, tc_017_2zone_muteB)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteB
TEST_F(ResultAPI_mute, tc_018_2zone_muteB_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteB
TEST_F(ResultAPI_mute, tc_019_2zone_muteB_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteB
TEST_F(ResultAPI_mute, tc_020_2zone_muteB_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA,B
TEST_F(ResultAPI_mute, tc_021_2zone_muteA_B)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA,B
TEST_F(ResultAPI_mute, tc_022_2zone_muteA_B_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_023_2zone_muteA_B_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_024_2zone_muteA_B_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

/**************************************************
 * Attenuated : ZoneA
 **************************************************/

// １つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_025_attnA_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_026_attnA_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_027_attnA_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_028_attnA_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンにコンテントの割り当てなし + mute
TEST_F(ResultAPI_mute, tc_029_attnA_mute_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1) + mute
TEST_F(ResultAPI_mute, tc_030_attnA_mute_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2) + mute
TEST_F(ResultAPI_mute, tc_031_attnA_mute_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2) + mute
TEST_F(ResultAPI_mute, tc_032_attnA_mute_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_033_attnA_2zone)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_034_attnA_2zone_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_035_attnA_2zone_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_036_attnA_2zone_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneB"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneB"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA
TEST_F(ResultAPI_mute, tc_037_attnA_2zone_muteA)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA
TEST_F(ResultAPI_mute, tc_038_attnA_2zone_muteA_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA
TEST_F(ResultAPI_mute, tc_039_attnA_2zone_muteA_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA
TEST_F(ResultAPI_mute, tc_040_attnA_2zone_muteA_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteB
TEST_F(ResultAPI_mute, tc_041_attnA_2zone_muteB)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteB
TEST_F(ResultAPI_mute, tc_042_attnA_2zone_muteB_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteB
TEST_F(ResultAPI_mute, tc_043_attnA_2zone_muteB_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteB
TEST_F(ResultAPI_mute, tc_044_attnA_2zone_muteB_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA,B
TEST_F(ResultAPI_mute, tc_045_attnA_2zone_muteA_B)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA,B
TEST_F(ResultAPI_mute, tc_046_attnA_2zone_muteA_B_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_047_attnA_2zone_muteA_B_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_048_attnA_2zone_muteA_B_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneAをAttenuated
  arb_->execute(u8"AttnA");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

/**************************************************
 * Attenuated : ZoneB
 **************************************************/

// １つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_049_attnB_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_050_attnB_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_051_attnB_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_052_attnB_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンにコンテントの割り当てなし + mute
TEST_F(ResultAPI_mute, tc_053_attnB_mute_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1) + mute
TEST_F(ResultAPI_mute, tc_054_attnB_mute_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2) + mute
TEST_F(ResultAPI_mute, tc_055_attnB_mute_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2) + mute
TEST_F(ResultAPI_mute, tc_056_attnB_mute_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_057_attnB_2zone)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_058_attnB_2zone_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_059_attnB_2zone_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_060_attnB_2zone_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneB"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneB"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA
TEST_F(ResultAPI_mute, tc_061_attnB_2zone_muteA)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA
TEST_F(ResultAPI_mute, tc_062_attnB_2zone_muteA_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA
TEST_F(ResultAPI_mute, tc_063_attnB_2zone_muteA_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA
TEST_F(ResultAPI_mute, tc_064_attnB_2zone_muteA_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteB
TEST_F(ResultAPI_mute, tc_065_attnB_2zone_muteB)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteB
TEST_F(ResultAPI_mute, tc_066_attnB_2zone_muteB_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteB
TEST_F(ResultAPI_mute, tc_067_attnB_2zone_muteB_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteB
TEST_F(ResultAPI_mute, tc_068_attnB_2zone_muteB_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA,B
TEST_F(ResultAPI_mute, tc_069_attnB_2zone_muteA_B)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA,B
TEST_F(ResultAPI_mute, tc_070_attnB_2zone_muteA_B_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_071_attnB_2zone_muteA_B_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_072_attnB_2zone_muteA_B_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneBをAttenuated
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

/**************************************************
 * Attenuated : ZoneA, ZoneB
 **************************************************/

// １つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_073_attnA_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_074_attnA_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_075_attnA_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_076_attnA_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンにコンテントの割り当てなし + mute
TEST_F(ResultAPI_mute, tc_077_attnA_mute_1zone)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZone);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent1) + mute
TEST_F(ResultAPI_mute, tc_078_attnA_mute_1zone_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに１つのコンテントが割り当て(SContent2) + mute
TEST_F(ResultAPI_mute, tc_079_attnA_mute_1zone_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのゾーンに２つのコンテントが割り当て(SContent1, SContent2) + mute
TEST_F(ResultAPI_mute, tc_080_attnA_mute_1zone_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし
TEST_F(ResultAPI_mute, tc_081_attnA_2zone)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)
TEST_F(ResultAPI_mute, tc_082_attnA_2zone_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(2u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)
TEST_F(ResultAPI_mute, tc_083_attnA_2zone_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(2u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)
TEST_F(ResultAPI_mute, tc_084_attnA_2zone_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(2u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState1.size());
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneB"));
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont1.size());
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont1, u8"ZoneB"));
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(0u, zonesByCont2.size());

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA
TEST_F(ResultAPI_mute, tc_085_attnA_2zone_muteA)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA
TEST_F(ResultAPI_mute, tc_086_attnA_2zone_muteA_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA
TEST_F(ResultAPI_mute, tc_087_attnA_2zone_muteA_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA
TEST_F(ResultAPI_mute, tc_088_attnA_2zone_muteA_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_TRUE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteB
TEST_F(ResultAPI_mute, tc_089_attnA_2zone_muteB)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteB
TEST_F(ResultAPI_mute, tc_090_attnA_2zone_muteB_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteB
TEST_F(ResultAPI_mute, tc_091_attnA_2zone_muteB_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteB
TEST_F(ResultAPI_mute, tc_092_attnA_2zone_muteB_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(1u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(1u, attnZones.size());
  EXPECT_TRUE(hasObject(attnZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_TRUE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンにコンテントの割り当てなし+muteA,B
TEST_F(ResultAPI_mute, tc_093_attnA_2zone_muteA_B)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(0u, muteZones.size());  
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont.size());

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #34 Mute check
  EXPECT_FALSE(result_->isMute(zoneA));
  EXPECT_FALSE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent1)+muteA,B
TEST_F(ResultAPI_mute, tc_094_attnA_2zone_muteA_B_cont1)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに１つのコンテントが割り当て(SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_095_attnA_2zone_muteA_B_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont2state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont2);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのゾーンに２つのコンテントが割り当て(SContent1, SContent2)+muteA,B
TEST_F(ResultAPI_mute, tc_096_attnA_2zone_muteA_B_cont1_cont2)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // ZoneA, ZoneBをAttenuated
  arb_->execute(u8"AttnA");
  arb_->execute(u8"AttnB");

  // mute ZoneA, ZoneB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #11 Mute Zone
  const std::list<const RBAZone*> muteZones = result_->getMuteZones();
  EXPECT_EQ(2u, muteZones.size());
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(muteZones, u8"ZoneB"));
  // #12 Attenuated Zone
  const std::list<const RBAZone*> attnZones = result_->getAttenuatedZones();
  EXPECT_EQ(0u, attnZones.size());
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_FALSE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #34 Mute check
  EXPECT_TRUE(result_->isMute(zoneA));
  EXPECT_TRUE(result_->isMute(zoneB));
  // #35 Attenuated check
  EXPECT_FALSE(result_->isAttenuated(zoneA));
  EXPECT_FALSE(result_->isAttenuated(zoneB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

}

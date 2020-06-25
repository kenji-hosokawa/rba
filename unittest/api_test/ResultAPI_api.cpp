// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_api.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_api.hpp"

namespace resultapi {

using namespace rba;

/**
 * APIテスト
 */
ResultAPI_api::ResultAPI_api()
{
  jsonFile = JSONFILE_API;
}

ResultAPI_api::~ResultAPI_api()
{
}

TEST_F(ResultAPI_api, tc_01_getVisibleAreas)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBAArea*> areas = result_->getVisibleAreas();
    EXPECT_EQ(0u, areas.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"ContentA1");
  {
    const std::list<const RBAArea*> areas = result_->getVisibleAreas();
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"ContentB1");
  {
    const std::list<const RBAArea*> areas = result_->getVisibleAreas();
    EXPECT_EQ(2u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
    EXPECT_TRUE(hasObject(areas, u8"AreaB"));
  }
}

TEST_F(ResultAPI_api, tc_02_getSoundingZones)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBAZone*> zones = result_->getSoundingZones();
    EXPECT_EQ(0u, zones.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"SContentA1");
  {
    const std::list<const RBAZone*> zones = result_->getSoundingZones();
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"SContentB1");
  {
    const std::list<const RBAZone*> zones = result_->getSoundingZones();
    EXPECT_EQ(2u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
    EXPECT_TRUE(hasObject(zones, u8"ZoneB"));
  }
}

TEST_F(ResultAPI_api, tc_03_getVisibleContentStates)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
    EXPECT_EQ(0u, states.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
    EXPECT_EQ(1u, states.size());
    EXPECT_TRUE(hasObject(states, u8"ContentA1/NORMAL"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"ContentB1/NORMAL");
  {
    const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
    EXPECT_EQ(2u, states.size());
    EXPECT_TRUE(hasObject(states, u8"ContentA1/NORMAL"));
    EXPECT_TRUE(hasObject(states, u8"ContentB1/NORMAL"));
  }
}

TEST_F(ResultAPI_api, tc_04_getSoundingContentStates)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getSoundingContentStates();
    EXPECT_EQ(0u, states.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getSoundingContentStates();
    EXPECT_EQ(1u, states.size());
    EXPECT_TRUE(hasObject(states, u8"SContentA1/NORMAL"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"SContentB1/NORMAL");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getSoundingContentStates();
    EXPECT_EQ(2u, states.size());
    EXPECT_TRUE(hasObject(states, u8"SContentA1/NORMAL"));
    EXPECT_TRUE(hasObject(states, u8"SContentB1/NORMAL"));
  }
}

TEST_F(ResultAPI_api, tc_05_getActiveViewContentStates)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBAViewContentState*> states
      = result_->getActiveViewContentStates();
    EXPECT_EQ(0u, states.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"ContentB1/NORMAL");
  {
    const std::list<const RBAViewContentState*> states
      = result_->getActiveViewContentStates();
    EXPECT_EQ(1u, states.size());
    EXPECT_TRUE(hasObject(states, u8"ContentB1/NORMAL"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"ContentB2/NORMAL");
  {
    const std::list<const RBAViewContentState*> states
      = result_->getActiveViewContentStates();
    EXPECT_EQ(2u, states.size());
    EXPECT_TRUE(hasObject(states, u8"ContentB1/NORMAL"));
    EXPECT_TRUE(hasObject(states, u8"ContentB2/NORMAL"));
  }
}

TEST_F(ResultAPI_api, tc_06_getActiveSoundContentStates)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getActiveSoundContentStates();
    EXPECT_EQ(0u, states.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"SContentB1/NORMAL");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getActiveSoundContentStates();
    EXPECT_EQ(1u, states.size());
    EXPECT_TRUE(hasObject(states, u8"SContentB1/NORMAL"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"SContentB2/NORMAL");
  {
    const std::list<const RBASoundContentState*> states
      = result_->getActiveSoundContentStates();
    EXPECT_EQ(2u, states.size());
    EXPECT_TRUE(hasObject(states, u8"SContentB1/NORMAL"));
    EXPECT_TRUE(hasObject(states, u8"SContentB2/NORMAL"));
  }
}

TEST_F(ResultAPI_api, tc_07_getActiveScenes)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    const std::list<const RBAScene*> scenes = result_->getActiveScenes();
    EXPECT_EQ(0u, scenes.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"SceneA");
  {
    const std::list<const RBAScene*> scenes = result_->getActiveScenes();
    EXPECT_EQ(1u, scenes.size());
    EXPECT_TRUE(hasObject(scenes, u8"SceneA"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"SceneB");
  {
    const std::list<const RBAScene*> scenes = result_->getActiveScenes();
    EXPECT_EQ(2u, scenes.size());
    EXPECT_TRUE(hasObject(scenes, u8"SceneA"));
    EXPECT_TRUE(hasObject(scenes, u8"SceneB"));
  }
}
  
TEST_F(ResultAPI_api, tc_08_getInvisibleAreas)
{
  // 出力要素数0
  result_ = arb_->execute(u8"ContentA1");
  result_ = arb_->execute(u8"ContentB1");
  {
    const std::list<const RBAArea*> areas = result_->getInvisibleAreas();
    EXPECT_EQ(0u, areas.size());
  }
  // 出力要素数1
   result_ = arb_->execute(u8"ContentB1", false);
  {
    const std::list<const RBAArea*> areas = result_->getInvisibleAreas();
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaB"));
  }
  // 出力要素数2
   result_ = arb_->execute(u8"ContentA1", false);
  {
    const std::list<const RBAArea*> areas = result_->getInvisibleAreas();
    EXPECT_EQ(2u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
    EXPECT_TRUE(hasObject(areas, u8"AreaB"));
  }
}

TEST_F(ResultAPI_api, tc_09_getUnsoundingZones)
{
  // 出力要素数0
  result_ = arb_->execute(u8"SContentA1");
  result_ = arb_->execute(u8"SContentB1");
  {
    const std::list<const RBAZone*> zones = result_->getUnsoundingZones();
    EXPECT_EQ(0u, zones.size());
  }
  // 出力要素数1
   result_ = arb_->execute(u8"SContentB1", false);
  {
    const std::list<const RBAZone*> zones = result_->getUnsoundingZones();
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneB"));
  }
  // 出力要素数2
   result_ = arb_->execute(u8"SContentA1", false);
  {
    const std::list<const RBAZone*> zones = result_->getUnsoundingZones();
    EXPECT_EQ(2u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
    EXPECT_TRUE(hasObject(zones, u8"ZoneB"));
  }
}

TEST_F(ResultAPI_api, tc_10_getHiddenAreas)
{
  // 出力要素数0
  result_ = arb_->execute(u8"SceneA");
  {
    const std::list<const RBAArea*> areas = result_->getHiddenAreas();
    EXPECT_EQ(0u, areas.size());
  }
  // 出力要素数1
   result_ = arb_->execute(u8"ContentA1");
  {
    const std::list<const RBAArea*> areas = result_->getHiddenAreas();
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
  }
  // 出力要素数1
   result_ = arb_->execute(u8"ContentB1");
  {
    const std::list<const RBAArea*> areas = result_->getHiddenAreas();
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
  }
}

TEST_F(ResultAPI_api, tc_11_getMuteZones)
{
  // 出力要素数0
  result_ = arb_->execute(u8"SceneA");
  {
    const std::list<const RBAZone*> zones = result_->getMuteZones();
    EXPECT_EQ(0u, zones.size());
  }
  // 出力要素数1
   result_ = arb_->execute(u8"SContentA1");
  {
    const std::list<const RBAZone*> zones = result_->getMuteZones();
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
  // 出力要素数1
   result_ = arb_->execute(u8"SContentB1");
  {
    const std::list<const RBAZone*> zones = result_->getMuteZones();
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
}

TEST_F(ResultAPI_api, tc_12_getAttenuatedZones)
{
  // 出力要素数0
  result_ = arb_->execute(u8"SceneB");
  {
    const std::list<const RBAZone*> zones = result_->getAttenuatedZones();
    EXPECT_EQ(0u, zones.size());
  }
  // 出力要素数1
   result_ = arb_->execute(u8"SContentA1");
  {
    const std::list<const RBAZone*> zones = result_->getAttenuatedZones();
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
  // 出力要素数2
   result_ = arb_->execute(u8"SContentB1");
  {
    const std::list<const RBAZone*> zones = result_->getAttenuatedZones();
    EXPECT_EQ(2u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
    EXPECT_TRUE(hasObject(zones, u8"ZoneB"));
  }
}

TEST_F(ResultAPI_api, tc_15_getStandbyViewContents)
{
  // 出力要素数0
  result_ = arb_->execute(u8"ContentB1");
  {
    const std::list<const RBAViewContent*> contents = result_->getStandbyViewContents();
    EXPECT_EQ(0u, contents.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"ContentB2");
  {
    const std::list<const RBAViewContent*> contents = result_->getStandbyViewContents();
    EXPECT_EQ(1u, contents.size());
    EXPECT_TRUE(hasObject(contents, u8"ContentB2"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"ContentB3");
  {
    const std::list<const RBAViewContent*> contents = result_->getStandbyViewContents();
    EXPECT_EQ(2u, contents.size());
    EXPECT_TRUE(hasObject(contents, u8"ContentB2"));
    EXPECT_TRUE(hasObject(contents, u8"ContentB3"));
  }
}

TEST_F(ResultAPI_api, tc_16_getStandbySoundContents)
{
  // 出力要素数0
  result_ = arb_->execute("SContentB1");
  {
    std::list<const RBASoundContent*> contents = result_->getStandbySoundContents();
    EXPECT_EQ(0u, contents.size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"SContentB2");
  {
    std::list<const RBASoundContent*> contents = result_->getStandbySoundContents();
    EXPECT_EQ(1u, contents.size());
    EXPECT_TRUE(hasObject(contents, u8"SContentB2"));
  }
  // 出力要素数2
  result_ = arb_->execute(u8"SContentB3");
  {
    std::list<const RBASoundContent*> contents = result_->getStandbySoundContents();
    EXPECT_EQ(2u, contents.size());
    EXPECT_TRUE(hasObject(contents, u8"SContentB2"));
    EXPECT_TRUE(hasObject(contents, u8"SContentB3"));
  }
}

TEST_F(ResultAPI_api, tc_17_getContentState_area)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBAViewContentState* state = result_->getContentState(area);
    EXPECT_EQ(nullptr, state);
  }
  // 出力あり
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBAViewContentState* state = result_->getContentState(area);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(u8"ContentA1/NORMAL", state->getUniqueName().c_str());
  }
  // 入力nullptr
  {
    const RBAArea* area = nullptr;
    const RBAViewContentState* state = result_->getContentState(area);
    EXPECT_EQ(nullptr, state);
  }
}

TEST_F(ResultAPI_api, tc_18_getContentState_zone)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    const RBASoundContentState* state = result_->getContentState(zone);
    EXPECT_EQ(nullptr, state);
  }
  // 出力あり
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    const RBASoundContentState* state = result_->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(u8"SContentA1/NORMAL", state->getUniqueName().c_str());
  }
  // 入力nullptr
  {
    const RBAZone* zone = nullptr;
    const RBASoundContentState* state = result_->getContentState(zone);
    EXPECT_EQ(nullptr, state);
  }
}

TEST_F(ResultAPI_api, tc_19_getArea_state)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAViewContentState* state
      = model_->findViewContentState(u8"ContentA1/NORMAL");
    const std::list<const RBAArea*> areas = result_->getArea(state);
    EXPECT_EQ(0u, areas.size());
  }
  // 出力あり
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAViewContentState* state
      = model_->findViewContentState(u8"ContentA1/NORMAL");
    const std::list<const RBAArea*> areas = result_->getArea(state);
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
  }
  // 入力nullptr
  {
    const RBAViewContentState* state = nullptr;
    const std::list<const RBAArea*> areas = result_->getArea(state);
    EXPECT_EQ(0u, areas.size());
  }
}

TEST_F(ResultAPI_api, tc_20_getZone_state)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBASoundContentState* state
      = model_->findSoundContentState(u8"SContentA1/NORMAL");
    const std::list<const RBAZone*> zones = result_->getZone(state);
    EXPECT_EQ(0u, zones.size());
  }
  // 出力あり
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBASoundContentState* state
      = model_->findSoundContentState(u8"SContentA1/NORMAL");
    const std::list<const RBAZone*> zones = result_->getZone(state);
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
  // 入力nullptr
  {
    const RBASoundContentState* state = nullptr;
    const std::list<const RBAZone*> zones = result_->getZone(state);
    EXPECT_EQ(0u, zones.size());
  }
}

TEST_F(ResultAPI_api, tc_21_getArea_content)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAViewContent* content = model_->findViewContent(u8"ContentA1");
    const std::list<const RBAArea*> areas = result_->getArea(content);
    EXPECT_EQ(0u, areas.size());
  }
  // 出力あり
  result_ = arb_->execute(u8"ContentA1");
  {
    const RBAViewContent* content = model_->findViewContent(u8"ContentA1");
    const std::list<const RBAArea*> areas = result_->getArea(content);
    EXPECT_EQ(1u, areas.size());
    EXPECT_TRUE(hasObject(areas, u8"AreaA"));
  }
  // 入力nullptr
  {
    const RBAViewContent* content = nullptr;
    const std::list<const RBAArea*> areas = result_->getArea(content);
    EXPECT_EQ(0u, areas.size());
  }
}

TEST_F(ResultAPI_api, tc_22_getZone_content)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBASoundContent* content = model_->findSoundContent(u8"SContentA1");
    const std::list<const RBAZone*> zones = result_->getZone(content);
    EXPECT_EQ(0u, zones.size());
  }
  // 出力あり
  result_ = arb_->execute(u8"SContentA1");
  {
    const RBASoundContent* content = model_->findSoundContent(u8"SContentA1");
    const std::list<const RBAZone*> zones = result_->getZone(content);
    EXPECT_EQ(1u, zones.size());
    EXPECT_TRUE(hasObject(zones, u8"ZoneA"));
  }
  // 入力nullptr
  {
    const RBASoundContent* content = nullptr;
    const std::list<const RBAZone*> zones = result_->getZone(content);
    EXPECT_EQ(0u, zones.size());
  }
}

TEST_F(ResultAPI_api, tc_23_getSize)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBASize* size = result_->getSize(area);
    EXPECT_EQ(nullptr, size);
  }
  // 出力あり
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBASize* size = result_->getSize(area);
    ASSERT_NE(nullptr, size);
    EXPECT_STREQ(u8"SizeA", size->getName().c_str());
  }
  // 入力nullptr
  {
    const RBAArea* area = nullptr;
    const RBASize* size = result_->getSize(area);
    EXPECT_EQ(nullptr, size);
  }
}

TEST_F(ResultAPI_api, tc_24_isActive_scene)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBAScene* scene = model_->findScene(u8"SceneA");
    EXPECT_FALSE(result_->isActive(scene));
  }
  // 出力true
  result_ = arb_->execute(u8"SceneA");
  {
    const RBAScene* scene = model_->findScene(u8"SceneA");
    EXPECT_TRUE(result_->isActive(scene));
  }
  // 入力nullptr
  {
    const RBAScene* scene = nullptr;
    EXPECT_FALSE(result_->isActive(scene));
  }
}

TEST_F(ResultAPI_api, tc_25_isActive_viewcontent)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBAViewContent* content = model_->findViewContent(u8"ContentA1");
    EXPECT_FALSE(result_->isActive(content));
  }
  // 出力true
  result_ = arb_->execute(u8"ContentA1");
  {
    const RBAViewContent* content = model_->findViewContent(u8"ContentA1");
    EXPECT_TRUE(result_->isActive(content));
  }
  // 入力nullptr
  {
    const RBAViewContent* content = nullptr;
    EXPECT_FALSE(result_->isActive(content));
  }
}

TEST_F(ResultAPI_api, tc_26_isActive_soundcontent)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBASoundContent* content = model_->findSoundContent(u8"SContentA1");
    EXPECT_FALSE(result_->isActive(content));
  }
  // 出力true
  result_ = arb_->execute(u8"SContentA1");
  {
    const RBASoundContent* content = model_->findSoundContent(u8"SContentA1");
    EXPECT_TRUE(result_->isActive(content));
  }
  // 入力nullptr
  {
    const RBASoundContent* content = nullptr;
    EXPECT_FALSE(result_->isActive(content));
  }
}

TEST_F(ResultAPI_api, tc_27_isVisible_area)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    EXPECT_FALSE(result_->isVisible(area));
  }
  // 出力true
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    EXPECT_TRUE(result_->isVisible(area));
  }
  // 入力nullptr
  {
    const RBAArea* area = nullptr;
    EXPECT_FALSE(result_->isVisible(area));
  }
}

TEST_F(ResultAPI_api, tc_28_isSounding_zone)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_FALSE(result_->isSounding(zone));
  }
  // 出力true
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_TRUE(result_->isSounding(zone));
  }
  // 入力nullptr
  {
    const RBAZone* zone = nullptr;
    EXPECT_FALSE(result_->isSounding(zone));
  }
}

TEST_F(ResultAPI_api, tc_29_isVisible_viewstate)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBAViewContentState* state
      = model_->findViewContentState(u8"ContentA1/NORMAL");
    EXPECT_FALSE(result_->isVisible(state));
  }
  // 出力true
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAViewContentState* state
      = model_->findViewContentState(u8"ContentA1/NORMAL");
    EXPECT_TRUE(result_->isVisible(state));
  }
  // 入力nullptr
  {
    const RBAViewContentState* state = nullptr;
    EXPECT_FALSE(result_->isVisible(state));
  }
}

TEST_F(ResultAPI_api, tc_30_isSounding_soundstate)
{
  // 出力false
  result_ = arb_->execute("");
  {
    const RBASoundContentState* state
      = model_->findSoundContentState(u8"SContentA1/NORMAL");
    EXPECT_FALSE(result_->isSounding(state));
  }
  // 出力true
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBASoundContentState* state
      = model_->findSoundContentState(u8"SContentA1/NORMAL");
    EXPECT_TRUE(result_->isSounding(state));
  }
  // 入力nullptr
  {
    const RBASoundContentState* state = nullptr;
    EXPECT_FALSE(result_->isSounding(state));
  }
}

TEST_F(ResultAPI_api, tc_31_getViewContentState)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBAViewContentState* state = result_->getViewContentState(area);
    EXPECT_EQ(nullptr, state);
  }
  // 出力あり
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    const RBAViewContentState* state = result_->getViewContentState(area);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(u8"ContentA1/NORMAL", state->getUniqueName().c_str());
  }
  // 入力nullptr
  {
    const RBAArea* area = nullptr;
    const RBAViewContentState* state = result_->getViewContentState(area);
    ASSERT_EQ(nullptr, state);
  }
}

TEST_F(ResultAPI_api, tc_32_getSoundContentState)
{
  // 出力nullptr
  result_ = arb_->execute("");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    const RBASoundContentState* state = result_->getSoundContentState(zone);
    EXPECT_EQ(nullptr, state);
  }
  // 出力あり
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    const RBASoundContentState* state = result_->getSoundContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(u8"SContentA1/NORMAL", state->getUniqueName().c_str());
  }
  // 入力nullptr
  {
    const RBAZone* zone = nullptr;
    const RBASoundContentState* state = result_->getSoundContentState(zone);
    ASSERT_EQ(nullptr, state);
  }
}

TEST_F(ResultAPI_api, tc_33_isHidden)
{
  // 出力false (not visible)
  result_ = arb_->execute("");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    EXPECT_FALSE(result_->isVisible(area));
    EXPECT_FALSE(result_->isHidden(area));
  }
  // 出力false (visible)
  result_ = arb_->execute(u8"ContentA1/NORMAL");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    EXPECT_TRUE(result_->isVisible(area));
    EXPECT_FALSE(result_->isHidden(area));
  }
  // 出力true
  result_ = arb_->execute(u8"SceneA");
  {
    const RBAArea* area = model_->findArea(u8"AreaA");
    EXPECT_FALSE(result_->isVisible(area));
    EXPECT_TRUE(result_->isHidden(area));
  }
  // 入力nullptr
  {
    const RBAArea* area = nullptr;
    EXPECT_FALSE(result_->isHidden(area));
  }
}

TEST_F(ResultAPI_api, tc_34_isMute)
{
  // 出力false (not sounding)
  result_ = arb_->execute("");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_FALSE(result_->isSounding(zone));
    EXPECT_FALSE(result_->isMute(zone));
  }
  // 出力false (sounding)
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_TRUE(result_->isSounding(zone));
    EXPECT_FALSE(result_->isMute(zone));
  }
  // 出力true
  result_ = arb_->execute(u8"SceneA");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_FALSE(result_->isSounding(zone));
    EXPECT_TRUE(result_->isMute(zone));
  }
  // 入力nullptr
  {
    const RBAZone* zone = nullptr;
    EXPECT_FALSE(result_->isMute(zone));
  }
}

TEST_F(ResultAPI_api, tc_35_isAttenuated)
{
  // 出力false (not sounding)
  result_ = arb_->execute("");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_FALSE(result_->isSounding(zone));
    EXPECT_FALSE(result_->isAttenuated(zone));
  }
  // 出力false (sounding)
  result_ = arb_->execute(u8"SContentA1/NORMAL");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_TRUE(result_->isSounding(zone));
    EXPECT_FALSE(result_->isAttenuated(zone));
  }
  // 出力true (not muted)
  result_ = arb_->execute(u8"SceneB");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_TRUE(result_->isSounding(zone));
    EXPECT_FALSE(result_->isMute(zone));
    EXPECT_TRUE(result_->isAttenuated(zone));
  }
  // 出力true (muted)
  result_ = arb_->execute(u8"SceneA");
  {
    const RBAZone* zone = model_->findZone(u8"ZoneA");
    EXPECT_FALSE(result_->isSounding(zone));
    EXPECT_TRUE(result_->isMute(zone));
    EXPECT_FALSE(result_->isAttenuated(zone));
  }
  // 入力nullptr
  {
    const RBAZone* zone = nullptr;
    EXPECT_FALSE(result_->isAttenuated(zone));
  }
}

TEST_F(ResultAPI_api, tc_38_getViewActions)
{
  // 出力要素数0
  result_ = arb_->execute("");
  {
    EXPECT_EQ(0u, result_->getViewActions().size());
  }
  // 出力要素数1
  result_ = arb_->execute(u8"ContentA2");
  {
    EXPECT_EQ(1u, result_->getViewActions().size());
  }
  // 出力要素数2
  std::list<std::string> contexts;
  contexts.push_back(u8"ContentA1");
  contexts.push_back(u8"ContentB1");
  result_ = arb_->execute(contexts, true);
  {
    EXPECT_EQ(2u, result_->getViewActions().size());
  }
}

TEST_F(ResultAPI_api, tc_39_getStatusType)
{
  // 成功
  result_ = arb_->execute("");
  {
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
  }
  // コンテントなしでエラー
  result_ = arb_->execute(u8"Unknown/NORMAL");
  {
    EXPECT_EQ(rba::RBAResultStatusType::UNKNOWN_CONTENT_STATE,
	      result_->getStatusType());
  }
  // ステートなしでエラー
  result_ = arb_->execute(u8"ContentA1/Unknown");
  {
    EXPECT_EQ(rba::RBAResultStatusType::UNKNOWN_CONTENT_STATE,
	      result_->getStatusType());
  }
  // シーンなしでエラー  
  result_ = arb_->execute(u8"UnknownScene");
  {
    EXPECT_EQ(rba::RBAResultStatusType::UNKNOWN_CONTENT_STATE,
	      result_->getStatusType());
  }
}

}

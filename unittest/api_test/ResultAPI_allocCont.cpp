// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_allocCont.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_allocCont.hpp"

namespace resultapi {

using namespace rba;

/*
 * Allocatable-Contentテスト
 */
ResultAPI_allocCont::ResultAPI_allocCont()
{
  jsonFile = JSONFILE_ALLOCATABLE_CONTENT;
}

ResultAPI_allocCont::~ResultAPI_allocCont()
{
}

// エリア数1(AreaA) : コンテント数1(Content1) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_01_1area_1cont)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(0u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(0u, states.size());

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(3u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  EXPECT_EQ(nullptr, stateByArea);
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(0u, areasByState.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(0u, areasByCont.size());

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  EXPECT_EQ(nullptr, size);

  // #27 Visible Area check
  EXPECT_FALSE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  EXPECT_EQ(nullptr, stateOfArea);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数1(Content1)  割り当てあり
TEST_F(ResultAPI_allocCont, tc_02_1area_1cont_cont1)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てあり
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数2(Content1,Content2) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_03_1area_2cont)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(0u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(0u, states.size());

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(3u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  EXPECT_EQ(nullptr, stateByArea);
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState1 = result_->getArea(cont1state);
  EXPECT_EQ(0u, areasByState1.size());
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState2 = result_->getArea(cont1state);
  EXPECT_EQ(0u, areasByState2.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont1 = result_->getArea(cont1);
  EXPECT_EQ(0u, areasByCont1.size());
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont2 = result_->getArea(cont2);
  EXPECT_EQ(0u, areasByCont2.size());

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  EXPECT_EQ(nullptr, size);

  // #27 Visible Area check
  EXPECT_FALSE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  EXPECT_EQ(nullptr, stateOfArea);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数2(Content1,Content2) Content1割り当て
TEST_F(ResultAPI_allocCont, tc_04_1area_2cont_cont1)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content1割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState1 = result_->getArea(cont1state);
  EXPECT_EQ(1u, areasByState1.size());
  EXPECT_TRUE(hasObject(areasByState1, u8"AreaA"));
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState2 = result_->getArea(cont2state);
  EXPECT_EQ(0u, areasByState2.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont1 = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont1.size());
  EXPECT_TRUE(hasObject(areasByCont1, u8"AreaA"));
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont2 = result_->getArea(cont2);
  EXPECT_EQ(0u, areasByCont2.size());

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数2(Content1,Content2) Content2割り当て
TEST_F(ResultAPI_allocCont, tc_05_1area_2cont_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content1割り当て
  result_ = arb_->execute(u8"Content2");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content2/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState1 = result_->getArea(cont1state);
  EXPECT_EQ(0u, areasByState1.size());
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState2 = result_->getArea(cont2state);
  EXPECT_EQ(1u, areasByState2.size());
  EXPECT_TRUE(hasObject(areasByState2, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont1 = result_->getArea(cont1);
  EXPECT_EQ(0u, areasByCont1.size());
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont2 = result_->getArea(cont2);
  EXPECT_EQ(1u, areasByCont2.size());
  EXPECT_TRUE(hasObject(areasByCont2, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数2(Content1,Content2) Content1, Content2割り当て
TEST_F(ResultAPI_allocCont, tc_06_1area_2cont_both)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content1, Content2割り当て
  std::list<std::string> contexts;
  contexts.push_back("Content1");
  contexts.push_back("Content2");
  result_ = arb_->execute(contexts);

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(1u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState1 = result_->getArea(cont1state);
  EXPECT_TRUE(hasObject(areasByState1, u8"AreaA"));
  EXPECT_EQ(1u, areasByState1.size());
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState2 = result_->getArea(cont2state);
  EXPECT_EQ(0u, areasByState2.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont1 = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont1.size());
  EXPECT_TRUE(hasObject(areasByCont1, u8"AreaA"));
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont2 = result_->getArea(cont2);
  EXPECT_EQ(0u, areasByCont2.size());

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数2(AreaA, AreaB) : コンテント数1(Content1) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_07_2area_1cont)
{
  // reaCを無効にする
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(0u, visibleAreas.size());
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(0u, states.size());

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(3u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  EXPECT_EQ(nullptr, stateByAreaA);
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  EXPECT_EQ(nullptr, stateByAreaB);
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(0u, areasByState.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(0u, areasByCont.size());

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  EXPECT_EQ(nullptr, size);

  // #27 Visible Area check
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  EXPECT_EQ(nullptr, stateOfAreaA);
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  EXPECT_EQ(nullptr, stateOfAreaB);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数2(AreaA, AreaB) : コンテント数1(Content1) AreaAに割り当てあり
TEST_F(ResultAPI_allocCont, tc_08_2area_1cont_AreaA)
{
  // AreaB,AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content1割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  EXPECT_EQ(nullptr, stateByAreaB);
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  EXPECT_EQ(nullptr, stateOfAreaB);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数2(AreaA, AreaB) : コンテント数1(Content1) AreaBに割り当てあり
TEST_F(ResultAPI_allocCont, tc_09_2area_2cont_AreaB)
{
  // AreaA,AreaCを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneCOff");

  // Content1割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  EXPECT_EQ(nullptr, stateByAreaA);
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaB"));

  // #23 Size
  const RBASize* size = result_->getSize(areaB);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeB", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_TRUE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  EXPECT_EQ(nullptr, stateOfAreaA);
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数2(AreaA, AreaB) : コンテント数1(Content1) AreaA,AreaBに割り当てあり
TEST_F(ResultAPI_allocCont, tc_10_2area_1cont_both)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content1割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(2u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(1u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(2u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaB"));

  // #23 Size
  const RBASize* sizeA = result_->getSize(areaA);
  ASSERT_NE(nullptr, sizeA);
  EXPECT_STREQ(u8"SizeA", sizeA->getName().c_str());
  const RBASize* sizeB = result_->getSize(areaB);
  ASSERT_NE(nullptr, sizeB);
  EXPECT_STREQ(u8"SizeB", sizeB->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  EXPECT_TRUE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数1(SContent1) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_11_1zone_1cont)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState.size());
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数1(SContent1)  割り当てあり
TEST_F(ResultAPI_allocCont, tc_12_1zone_1cont_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てあり
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
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

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
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数2(SContent1,SContent2) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_13_1zone_2cont)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZone);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState1.size());
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by SContent
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont1.size());
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
  EXPECT_EQ(nullptr, stateOfZone);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数2(SContent1,SContent2) SContent1割り当て
TEST_F(ResultAPI_allocCont, tc_14_1zone_2cont_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // SContent1割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

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
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数2(SContent1,SContent2) SContent2割り当て
TEST_F(ResultAPI_allocCont, tc_15_1zone_2cont_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // SContent1割り当て
  result_ = arb_->execute(u8"SContent2");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent2/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_EQ(0u, zonesByState1.size());
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(1u, zonesByState2.size());
  EXPECT_TRUE(hasObject(zonesByState2, u8"ZoneA"));
  // #22 Zone by SContent
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont1 = result_->getZone(cont1);
  EXPECT_EQ(0u, zonesByCont1.size());
  const RBASoundContent* cont2 = model_->findSoundContent(u8"SContent2");
  const std::list<const RBAZone*> zonesByCont2 = result_->getZone(cont2);
  EXPECT_EQ(1u, zonesByCont2.size());
  EXPECT_TRUE(hasObject(zonesByCont2, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_FALSE(result_->isSounding(cont1state));
  EXPECT_TRUE(result_->isSounding(cont2state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent2/NORMAL", stateOfZone->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数2(SContent1,SContent2) SContent1, SContent2割り当て
TEST_F(ResultAPI_allocCont, tc_16_1zone_2cont_both)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // SContent1, SContent2割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  result_ = arb_->execute(contexts);

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState1 = result_->getZone(cont1state);
  EXPECT_TRUE(hasObject(zonesByState1, u8"ZoneA"));
  EXPECT_EQ(1u, zonesByState1.size());
  const RBASoundContentState* cont2state
    = model_->findSoundContentState(u8"SContent2/NORMAL");
  const std::list<const RBAZone*> zonesByState2 = result_->getZone(cont2state);
  EXPECT_EQ(0u, zonesByState2.size());
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数2(ZoneA, ZoneB) : コンテント数1(SContent1) 割り当てなし
TEST_F(ResultAPI_allocCont, tc_17_2zone_1cont)
{
  // reaCを無効にする
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute("");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(0u, soundingZones.size());
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(0u, states.size());

  // #09 Unsounding Zone
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(3u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

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
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数2(ZoneA, ZoneB) : コンテント数1(SContent1) ZoneAに割り当てあり
TEST_F(ResultAPI_allocCont, tc_18_2zone_1cont_ZoneA)
{
  // ZoneB,ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // SContent1割り当て
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
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneA->getUniqueName().c_str());
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  EXPECT_EQ(nullptr, stateByZoneB);
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by SContent
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

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
  EXPECT_EQ(nullptr, stateOfZoneB);

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数2(ZoneA, ZoneB) : コンテント数1(SContent1) ZoneBに割り当てあり
TEST_F(ResultAPI_allocCont, tc_19_2zone_1cont_ZoneB)
{
  // ZoneA,ZoneCを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneCOff");

  // SContent1割り当て
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
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZoneA = result_->getContentState(zoneA);
  EXPECT_EQ(nullptr, stateByZoneA);
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by SContent
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_FALSE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  EXPECT_EQ(nullptr, stateOfZoneA);
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数2(ZoneA, ZoneB) : コンテント数1(SContent1) ZoneA,ZoneBに割り当てあり
TEST_F(ResultAPI_allocCont, tc_20_2zone_1cont_both)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // SContent1割り当て
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
  const std::list<const RBAZone*> insoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, insoundingZones.size());
  EXPECT_TRUE(hasObject(insoundingZones, u8"ZoneC"));
  // #16 Standby SContent
  std::list<const RBASoundContent*> standbySContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbySContents.size());

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
  // #22 Zone by SContent
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

}

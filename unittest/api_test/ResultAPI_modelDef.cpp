// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_result_api.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_modelDef.hpp"

namespace resultapi {

using namespace rba;

/*
 * モデル定義順テスト
 */
ResultAPI_modelDef::ResultAPI_modelDef()
{
  jsonFile = JSONFILE_ALLOCATABLE_CONTENT;
}

ResultAPI_modelDef::~ResultAPI_modelDef()
{
}

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// 最初のコンテント(Content1)が割り当て
TEST_F(ResultAPI_modelDef, tc_01_1area_3cont_cont1)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 最初のコンテントを割り当て
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

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// ２番目のコンテント(Content2)が割り当て
TEST_F(ResultAPI_modelDef, tc_02_1area_3cont_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ２番目のコンテントを割り当て
  result_ = arb_->execute(u8"Content2");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
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
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// 最後のコンテント(Content3)が割り当て
TEST_F(ResultAPI_modelDef, tc_03_1area_3cont_cont3)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 最後のコンテントを割り当て
  result_ = arb_->execute(u8"Content3");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content3/NORMAL"));

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
  EXPECT_STREQ(u8"Content3/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont3state
    = model_->findViewContentState(u8"Content3/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont3state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont3 = model_->findViewContent(u8"Content3");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont3);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont3state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content3/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// １、２番目のコンテント(Content1, Content2)が割り当て
TEST_F(ResultAPI_modelDef, tc_04_1area_3cont_cont1_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // １、２番目のコンテントを割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  result_ = arb_->execute(contexts);

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
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));

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

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// ２、３番目のコンテント(Content2, Content3)が割り当て
TEST_F(ResultAPI_modelDef, tc_05_1area_3cont_cont2_cont3)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ２、３番目のコンテントを割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"Content2");
  contexts.push_back(u8"Content3");
  result_ = arb_->execute(contexts);

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
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
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content3"));

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByArea = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));

  // #23 Size
  const RBASize* size = result_->getSize(areaA);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeA", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数1(AreaA) : コンテント数3(Content1, Content2, Conetnt3)
// 全てのコンテント(Content1, Content2, Content3)が割り当て
TEST_F(ResultAPI_modelDef, tc_04_1area_3cont_allcont)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 全てのコンテントを割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  contexts.push_back(u8"Content3");
  result_ = arb_->execute(contexts);

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
  EXPECT_EQ(2u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));
  EXPECT_TRUE(hasObject(standbyContents, u8"Content3"));

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

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// 最初のアロケータブル(AreaA)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_07_3area_1cont_AreaA)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// ２番目のアロケータブル(AreaB)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_08_3area_1cont_AreaB)
{
  // AreaA, AreaCを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByArea = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByArea->getUniqueName().c_str());
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
  EXPECT_TRUE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// 最後のアロケータブル(AreaC)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_09_3area_1cont_AreaC)
{
  // AreaA, AreaBを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneBOff");

  // コンテントを割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaC"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaB"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaC = model_->findArea(u8"AreaC");
  const RBAViewContentState* stateByArea = result_->getContentState(areaC);
  ASSERT_NE(nullptr, stateByArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByArea->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(1u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaC"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(1u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaC"));

  // #23 Size
  const RBASize* size = result_->getSize(areaC);
  ASSERT_NE(nullptr, size);
  EXPECT_STREQ(u8"SizeC", size->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaC));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaC);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// １、２番目のアロケータブル(AreaA, AreaB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_10_3area_1cont_AreaA_AreaB)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// ２、３番目のアロケータブル(AreaA, AreaB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_11_3area_1cont_AreaB_AreaC)
{
  // AreaAを無効にする
  arb_->execute(u8"SceneAOff");

  // コンテントを割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(2u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaC"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(1u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaB->getUniqueName().c_str());
  const RBAArea* areaC = model_->findArea(u8"AreaC");
  const RBAViewContentState* stateByAreaC = result_->getContentState(areaC);
  ASSERT_NE(nullptr, stateByAreaC);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaC->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaC"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(2u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaB"));
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaC"));

  // #23 Size
  const RBASize* sizeB = result_->getSize(areaB);
  ASSERT_NE(nullptr, sizeB);
  EXPECT_STREQ(u8"SizeB", sizeB->getName().c_str());
  const RBASize* sizeC = result_->getSize(areaC);
  ASSERT_NE(nullptr, sizeC);
  EXPECT_STREQ(u8"SizeC", sizeC->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaB));
  EXPECT_TRUE(result_->isVisible(areaC));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaC = result_->getViewContentState(areaC);
  ASSERT_NE(nullptr, stateOfAreaC);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaC->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// エリア数3(AreaA, AreaB, AreaC) : コンテント数1(Content1)
// 全てのアロケータブル(AreaA, AreaB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_12_3area_1cont_allarea)
{
  // コンテントを割り当て
  result_ = arb_->execute(u8"Content1");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(3u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaC"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content1/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(0u, invisibleAreas.size());
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
  const RBAArea* areaC = model_->findArea(u8"AreaC");
  const RBAViewContentState* stateByAreaC = result_->getContentState(areaC);
  ASSERT_NE(nullptr, stateByAreaC);
  EXPECT_STREQ(u8"Content1/NORMAL", stateByAreaC->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont1state
    = model_->findViewContentState(u8"Content1/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont1state);
  EXPECT_EQ(3u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaC"));
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont1);
  EXPECT_EQ(3u, areasByCont.size());
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaB"));
  EXPECT_TRUE(hasObject(areasByCont, u8"AreaC"));

  // #23 Size
  const RBASize* sizeA = result_->getSize(areaA);
  ASSERT_NE(nullptr, sizeA);
  EXPECT_STREQ(u8"SizeA", sizeA->getName().c_str());
  const RBASize* sizeB = result_->getSize(areaB);
  ASSERT_NE(nullptr, sizeB);
  EXPECT_STREQ(u8"SizeB", sizeB->getName().c_str());
  const RBASize* sizeC = result_->getSize(areaC);
  ASSERT_NE(nullptr, sizeC);
  EXPECT_STREQ(u8"SizeC", sizeC->getName().c_str());

  // #27 Visible Area check
  EXPECT_TRUE(result_->isVisible(areaA));
  EXPECT_TRUE(result_->isVisible(areaB));
  EXPECT_TRUE(result_->isVisible(areaC));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaC = result_->getViewContentState(areaC);
  ASSERT_NE(nullptr, stateOfAreaC);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaC->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, SConetnt3)
// 最初のコンテント(SContent1)が割り当て
TEST_F(ResultAPI_modelDef, tc_13_1zone_3cont_cont1)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 最初のコンテントを割り当て
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, Conetnt3)
// ２番目のコンテント(SContent2)が割り当て
TEST_F(ResultAPI_modelDef, tc_14_1zone_3cont_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ２番目のコンテントを割り当て
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, Conetnt3)
// 最後のコンテント(SContent3)が割り当て
TEST_F(ResultAPI_modelDef, tc_15_1zone_3cont_cont3)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 最後のコンテントを割り当て
  result_ = arb_->execute(u8"SContent3");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent3/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneC"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneA = model_->findZone(u8"ZoneA");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneA);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent3/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont3state
    = model_->findSoundContentState(u8"SContent3/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont3state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  // #22 Zone by Content
  const RBASoundContent* cont3 = model_->findSoundContent(u8"SContent3");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont3);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont3state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent3/NORMAL", stateOfZone->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, Conetnt3)
// １、２番目のコンテント(SContent1, SContent2)が割り当て
TEST_F(ResultAPI_modelDef, tc_16_1zone_3cont_cont1_cont2)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // １、２番目のコンテントを割り当て
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, Conetnt3)
// ２、３番目のコンテント(SContent2, SContent3)が割り当て
TEST_F(ResultAPI_modelDef, tc_17_1zone_3cont_cont2_cont3)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ２、３番目のコンテントを割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent2");
  contexts.push_back(u8"SContent3");
  result_ = arb_->execute(contexts);

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
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent3"));

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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数1(ZoneA) : コンテント数3(SContent1, SContent2, Conetnt3)
// 全てのコンテント(SContent1, SContent2, SContent3)が割り当て
TEST_F(ResultAPI_modelDef, tc_18_1zone_3cont_allcont)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 全てのコンテントを割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"SContent1");
  contexts.push_back(u8"SContent2");
  contexts.push_back(u8"SContent3");
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
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(2u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent2"));
  EXPECT_TRUE(hasObject(standbyContents, u8"SContent3"));

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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// 最初のアロケータブル(ZoneA)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_19_3zone_1cont_ZoneA)
{
  // ZoneB, ZoneCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// ２番目のアロケータブル(ZoneB)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_20_3zone_1cont_ZoneB)
{
  // ZoneA, ZoneCを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneB));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// 最後のアロケータブル(ZoneC)にコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_21_3zone_1cont_ZoneC)
{
  // ZoneA, ZoneBを無効にする
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneBOff");

  // コンテントを割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(1u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneC"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(2u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneB"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneC = model_->findZone(u8"ZoneC");
  const RBASoundContentState* stateByZone = result_->getContentState(zoneC);
  ASSERT_NE(nullptr, stateByZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZone->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(1u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneC"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(1u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneC"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneC));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZone = result_->getSoundContentState(zoneC);
  ASSERT_NE(nullptr, stateOfZone);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZone->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// １、２番目のアロケータブル(ZoneA, ZoneB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_22_3zone_1cont_ZoneA_ZoneB)
{
  // ZoneCを無効にする
  arb_->execute(u8"SceneCOff");

  // コンテントを割り当て
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

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// ２、３番目のアロケータブル(ZoneA, ZoneB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_23_3zone_1cont_ZoneB_ZoneC)
{
  // ZoneAを無効にする
  arb_->execute(u8"SceneAOff");

  // コンテントを割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(2u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneC"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(1u, unsoundingZones.size());
  EXPECT_TRUE(hasObject(unsoundingZones, u8"ZoneA"));
  // #16 Standby Content
  std::list<const RBASoundContent*> standbyContents
    = result_->getStandbySoundContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #18 State by Zone
  const RBAZone* zoneB = model_->findZone(u8"ZoneB");
  const RBASoundContentState* stateByZoneB = result_->getContentState(zoneB);
  ASSERT_NE(nullptr, stateByZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneB->getUniqueName().c_str());
  const RBAZone* zoneC = model_->findZone(u8"ZoneC");
  const RBASoundContentState* stateByZoneC = result_->getContentState(zoneC);
  ASSERT_NE(nullptr, stateByZoneC);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneC->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(2u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneC"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(2u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneC"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneB));
  EXPECT_TRUE(result_->isSounding(zoneC));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneC = result_->getSoundContentState(zoneC);
  ASSERT_NE(nullptr, stateOfZoneC);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneC->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ゾーン数3(ZoneA, ZoneB, ZoneC) : コンテント数1(SContent1)
// 全てのアロケータブル(ZoneA, ZoneB)に同じコンテンツが割り当て
TEST_F(ResultAPI_modelDef, tc_24_3zone_1cont_allzone)
{
  // コンテントを割り当て
  result_ = arb_->execute(u8"SContent1");

  // #02 Sounding Zone
  const std::list<const RBAZone*> soundingZones = result_->getSoundingZones();
  EXPECT_EQ(3u, soundingZones.size());
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneA"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneB"));
  EXPECT_TRUE(hasObject(soundingZones, u8"ZoneC"));
  // #04 Sounding State
  const std::list<const RBASoundContentState*> states = result_->getSoundingContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"SContent1/NORMAL"));

  // #09 Unsounding Zone
  const std::list<const RBAZone*> unsoundingZones = result_->getUnsoundingZones();
  EXPECT_EQ(0u, unsoundingZones.size());
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
  const RBAZone* zoneC = model_->findZone(u8"ZoneC");
  const RBASoundContentState* stateByZoneC = result_->getContentState(zoneC);
  ASSERT_NE(nullptr, stateByZoneC);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateByZoneC->getUniqueName().c_str());
  // #20 Zone by State
  const RBASoundContentState* cont1state
    = model_->findSoundContentState(u8"SContent1/NORMAL");
  const std::list<const RBAZone*> zonesByState = result_->getZone(cont1state);
  EXPECT_EQ(3u, zonesByState.size());
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneB"));
  EXPECT_TRUE(hasObject(zonesByState, u8"ZoneC"));
  // #22 Zone by Content
  const RBASoundContent* cont1 = model_->findSoundContent(u8"SContent1");
  const std::list<const RBAZone*> zonesByCont = result_->getZone(cont1);
  EXPECT_EQ(3u, zonesByCont.size());
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneA"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneB"));
  EXPECT_TRUE(hasObject(zonesByCont, u8"ZoneC"));

  // #28 Sounding Zone check
  EXPECT_TRUE(result_->isSounding(zoneA));
  EXPECT_TRUE(result_->isSounding(zoneB));
  EXPECT_TRUE(result_->isSounding(zoneC));
  // #30 Sounding State check
  EXPECT_TRUE(result_->isSounding(cont1state));
  // #32 State by Zone
  const RBASoundContentState* stateOfZoneA = result_->getSoundContentState(zoneA);
  ASSERT_NE(nullptr, stateOfZoneA);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneA->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneB = result_->getSoundContentState(zoneB);
  ASSERT_NE(nullptr, stateOfZoneB);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneB->getUniqueName().c_str());
  const RBASoundContentState* stateOfZoneC = result_->getSoundContentState(zoneC);
  ASSERT_NE(nullptr, stateOfZoneC);
  EXPECT_STREQ(u8"SContent1/NORMAL", stateOfZoneC->getUniqueName().c_str());

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

}

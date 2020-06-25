// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_hidden.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_hidden.hpp"

namespace resultapi {

using namespace rba;

/*
 * hiddenテスト
 */
ResultAPI_hidden::ResultAPI_hidden()
{
  jsonFile = JSONFILE_ALLOCATABLE_CONTENT;
}

ResultAPI_hidden::~ResultAPI_hidden()
{
}

// １つのエリアにコンテントの割り当てなし
TEST_F(ResultAPI_hidden, tc_01_1area)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに１つのコンテントが割り当て(Content1)
TEST_F(ResultAPI_hidden, tc_02_1area_cont1)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに１つのコンテントが割り当て(Content2)
TEST_F(ResultAPI_hidden, tc_03_1area_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに２つのコンテントが割り当て(Content1, Content2)
TEST_F(ResultAPI_hidden, tc_04_1area_cont1_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // Content割り当
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアにコンテントの割り当てなし + hidden
TEST_F(ResultAPI_hidden, tc_05_hidden_1area)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに１つのコンテントが割り当て(Content1) + hidden
TEST_F(ResultAPI_hidden, tc_06_hidden_1area_cont1)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"Content1");

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
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
  EXPECT_FALSE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに１つのコンテントが割り当て(Content2) + hidden
TEST_F(ResultAPI_hidden, tc_07_hidden_1area_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  result_ = arb_->execute(u8"Content2");

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
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
  EXPECT_FALSE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfArea->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// １つのエリアに２つのコンテントが割り当て(Content1, Content2) + hidden
TEST_F(ResultAPI_hidden, tc_08_hidden_1area_cont1_cont2)
{
  // AreaB, AreaCを無効にする
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  result_ = arb_->execute(contexts);

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
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
  EXPECT_FALSE(result_->isVisible(areaA));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfArea = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfArea);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfArea->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアにコンテントの割り当てなし
TEST_F(ResultAPI_hidden, tc_09_2area)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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
  const RBASize* sizeA = result_->getSize(areaA);
  EXPECT_EQ(nullptr, sizeA);
  const RBASize* sizeB = result_->getSize(areaB);
  EXPECT_EQ(nullptr, sizeB);

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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content1)
TEST_F(ResultAPI_hidden, tc_10_2area_cont1)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content2)
TEST_F(ResultAPI_hidden, tc_11_2area_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
  result_ = arb_->execute(u8"Content2");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(2u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content2/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(1u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
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
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに２つのコンテントが割り当て(Content1, Content2)
TEST_F(ResultAPI_hidden, tc_12_2area_cont1_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // Content割り当
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  result_ = arb_->execute(contexts);

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));

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
  const std::list<const RBAArea*> areasByState1 = result_->getArea(cont1state);
  EXPECT_EQ(2u, areasByState1.size());
  EXPECT_TRUE(hasObject(areasByState1, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState1, u8"AreaB"));
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState2 = result_->getArea(cont2state);
  EXPECT_EQ(0u, areasByState2.size());
  // #21 Area by Content
  const RBAViewContent* cont1 = model_->findViewContent(u8"Content1");
  const std::list<const RBAArea*> areasByCont1 = result_->getArea(cont1);
  EXPECT_EQ(2u, areasByCont1.size());
  EXPECT_TRUE(hasObject(areasByCont1, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByCont1, u8"AreaB"));
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont2 = result_->getArea(cont2);
  EXPECT_EQ(0u, areasByCont2.size());

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
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアにコンテントの割り当てなし+hiddenA
TEST_F(ResultAPI_hidden, tc_13_2area_hiddenA)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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
  const RBASize* sizeA = result_->getSize(areaA);
  EXPECT_EQ(nullptr, sizeA);
  const RBASize* sizeB = result_->getSize(areaB);
  EXPECT_EQ(nullptr, sizeB);

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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content1)+hiddenA
TEST_F(ResultAPI_hidden, tc_14_2area_hiddenA_cont1)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
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
  EXPECT_FALSE(result_->isVisible(areaA));
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

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content2)+hiddenA
TEST_F(ResultAPI_hidden, tc_15_2area_hiddenA_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  result_ = arb_->execute(u8"Content2");

  // #01 Visible Area
  const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
  EXPECT_EQ(1u, visibleAreas.size());
  EXPECT_TRUE(hasObject(visibleAreas, u8"AreaB"));
  // #03 Visible State
  const std::list<const RBAViewContentState*> states = result_->getVisibleContentStates();
  EXPECT_EQ(1u, states.size());
  EXPECT_TRUE(hasObject(states, u8"Content2/NORMAL"));

  // #08 Invisible Area
  const std::list<const RBAArea*> invisibleAreas = result_->getInvisibleAreas();
  EXPECT_EQ(2u, invisibleAreas.size());
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(invisibleAreas, u8"AreaC"));
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
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
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_TRUE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに２つのコンテントが割り当て(Content1, Content2)+hiddenA
TEST_F(ResultAPI_hidden, tc_16_2area_hiddenA_cont1_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA
  arb_->execute(u8"HiddenMuteA");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  result_ = arb_->execute(contexts);

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));

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
  EXPECT_FALSE(result_->isVisible(areaA));
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

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアにコンテントの割り当てなし+hiddenB
TEST_F(ResultAPI_hidden, tc_17_2area_hiddenB)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaB
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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
  const RBASize* sizeA = result_->getSize(areaA);
  EXPECT_EQ(nullptr, sizeA);
  const RBASize* sizeB = result_->getSize(areaB);
  EXPECT_EQ(nullptr, sizeB);

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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content1)+hiddenB
TEST_F(ResultAPI_hidden, tc_18_2area_hiddenB_cont1)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
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
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content2)+hiddenB
TEST_F(ResultAPI_hidden, tc_19_2area_hiddenB_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
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
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに２つのコンテントが割り当て(Content1, Content2)+hiddenB
TEST_F(ResultAPI_hidden, tc_20_2area_hiddenB_cont1_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaB
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(1u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));

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
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_TRUE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアにコンテントの割り当てなし+hiddenA,B
TEST_F(ResultAPI_hidden, tc_21_2area_hiddenA_B)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA, AreaB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // 割り当てなし
  result_ = arb_->execute();

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(0u, hiddenAreas.size());  
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
  const RBASize* sizeA = result_->getSize(areaA);
  EXPECT_EQ(nullptr, sizeA);
  const RBASize* sizeB = result_->getSize(areaB);
  EXPECT_EQ(nullptr, sizeB);

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

  // #33 Hidden check
  EXPECT_FALSE(result_->isHidden(areaA));
  EXPECT_FALSE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content1)+hiddenA,B
TEST_F(ResultAPI_hidden, tc_22_2area_hiddenA_B_cont1)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA, AreaB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"Content1");

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(2u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
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
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに１つのコンテントが割り当て(Content2)+hiddenA,B
TEST_F(ResultAPI_hidden, tc_23_2area_hiddenA_B_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA, AreaB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  result_ = arb_->execute(u8"Content2");

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(2u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(0u, standbyContents.size());

  // #17 State by Area
  const RBAArea* areaA = model_->findArea(u8"AreaA");
  const RBAViewContentState* stateByAreaA = result_->getContentState(areaA);
  ASSERT_NE(nullptr, stateByAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaA->getUniqueName().c_str());
  const RBAArea* areaB = model_->findArea(u8"AreaB");
  const RBAViewContentState* stateByAreaB = result_->getContentState(areaB);
  ASSERT_NE(nullptr, stateByAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateByAreaB->getUniqueName().c_str());
  // #19 Area by State
  const RBAViewContentState* cont2state
    = model_->findViewContentState(u8"Content2/NORMAL");
  const std::list<const RBAArea*> areasByState = result_->getArea(cont2state);
  EXPECT_EQ(2u, areasByState.size());
  EXPECT_TRUE(hasObject(areasByState, u8"AreaA"));
  EXPECT_TRUE(hasObject(areasByState, u8"AreaB"));
  // #21 Area by Content
  const RBAViewContent* cont2 = model_->findViewContent(u8"Content2");
  const std::list<const RBAArea*> areasByCont = result_->getArea(cont2);
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
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont2state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content2/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

// ２つのエリアに２つのコンテントが割り当て(Content1, Content2)+hiddenA,B
TEST_F(ResultAPI_hidden, tc_24_2area_hiddenA_B_cont1_cont2)
{
  // AreaCを無効にする
  arb_->execute(u8"SceneCOff");

  // hidden AreaA, AreaB
  arb_->execute(u8"HiddenMuteA");
  arb_->execute(u8"HiddenMuteB");

  // Content割り当て
  std::list<std::string> contexts;
  contexts.push_back(u8"Content1");
  contexts.push_back(u8"Content2");
  result_ = arb_->execute(contexts);

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
  // #10 Hidden Area
  const std::list<const RBAArea*> hiddenAreas = result_->getHiddenAreas();
  EXPECT_EQ(2u, hiddenAreas.size());
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaA"));
  EXPECT_TRUE(hasObject(hiddenAreas, u8"AreaB"));
  // #15 Standby Content
  const std::list<const RBAViewContent*> standbyContents
    = result_->getStandbyViewContents();
  EXPECT_EQ(1u, standbyContents.size());
  EXPECT_TRUE(hasObject(standbyContents, u8"Content2"));

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
  EXPECT_FALSE(result_->isVisible(areaA));
  EXPECT_FALSE(result_->isVisible(areaB));
  // #29 Visible State check
  EXPECT_FALSE(result_->isVisible(cont1state));
  // #31 State by Area
  const RBAViewContentState* stateOfAreaA = result_->getViewContentState(areaA);
  ASSERT_NE(nullptr, stateOfAreaA);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaA->getUniqueName().c_str());
  const RBAViewContentState* stateOfAreaB = result_->getViewContentState(areaB);
  ASSERT_NE(nullptr, stateOfAreaB);
  EXPECT_STREQ(u8"Content1/NORMAL", stateOfAreaB->getUniqueName().c_str());

  // #33 Hidden check
  EXPECT_TRUE(result_->isHidden(areaA));
  EXPECT_TRUE(result_->isHidden(areaB));

  // #39 Staus
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_viewaction.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI_viewaction.hpp"

namespace resultapi {

using namespace rba;

/**
 * ViewActionテスト
 */
ResultAPI_viewaction::ResultAPI_viewaction()
{
  jsonFile = JSONFILE_ALLOCATABLE_CONTENT;
}

ResultAPI_viewaction::~ResultAPI_viewaction()
{
}

TEST_F(ResultAPI_viewaction, tc_01_forward)
{
  // initialize
  arb_->execute(u8"SceneBOff");
  arb_->execute(u8"SceneCOff");

  // ADD:AreaA = Content1
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"Content1");
    contexts.push_back(u8"Content2");
    result_ = arb_->execute(contexts);  // Context2は調停負けで非表示

    // check ADD
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaA", area->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());
  }

  // MOVE:AreaA -> AreaB
  {
    std::list<std::pair<std::string, std::int32_t>> props;
    arb_->setScene(u8"SceneBOff", false, props);
    result_ = arb_->execute(u8"SceneAOff");

    // check MOVE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::MOVE, va->getViewActionType());
    const RBAArea* areaFrom = va->getFromArea();
    EXPECT_STREQ(u8"AreaA", areaFrom->getName().c_str());
    const RBAArea* areaTo = va->getToArea();
    EXPECT_STREQ(u8"AreaB", areaTo->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());
  }

  // REPLACE:AreaB Content1 -> Content2
  {
    result_ = arb_->execute(u8"Content1", false);

    // check REPLACE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_REPLACE, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaB", area->getName().c_str());
    const RBAViewContent* contFrom = va->getFromContent();
    EXPECT_STREQ(u8"Content1", contFrom->getName().c_str());
    const RBAViewContent* contTo = va->getToContent();
    EXPECT_STREQ(u8"Content2", contTo->getName().c_str());
  }

  // REMOVE:AreaB Content1
  {
    result_ = arb_->execute(u8"Content2", false);

    // check REMOVE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_REMOVE, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaB", area->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content2", cont->getName().c_str());
  }
}

TEST_F(ResultAPI_viewaction, tc_02_revese)
{
  // initialize
  arb_->execute(u8"SceneAOff");
  arb_->execute(u8"SceneCOff");

  // ADD:AreaB = Content2
  {
    result_ = arb_->execute(u8"Content2");

    // check ADD
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaB", area->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content2", cont->getName().c_str());
  }

  // REPLACE:AreaB Content2 -> Content1
  {
    result_ = arb_->execute(u8"Content1");

    // check REPLACE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_REPLACE, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaB", area->getName().c_str());
    const RBAViewContent* contFrom = va->getFromContent();
    EXPECT_STREQ(u8"Content2", contFrom->getName().c_str());
    const RBAViewContent* contTo = va->getToContent();
    EXPECT_STREQ(u8"Content1", contTo->getName().c_str());
  }

  
  // MOVE:AreaB -> AreaA
  {
    std::list<std::pair<std::string, std::int32_t>> props;
    arb_->setScene(u8"SceneAOff", false, props);
    result_ = arb_->execute(u8"SceneBOff");

    // check MOVE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::MOVE, va->getViewActionType());
    const RBAArea* areaFrom = va->getFromArea();
    EXPECT_STREQ(u8"AreaB", areaFrom->getName().c_str());
    const RBAArea* areaTo = va->getToArea();
    EXPECT_STREQ(u8"AreaA", areaTo->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());
  }

  // REMOVE:AreaB Content1
  {
    result_ = arb_->execute(u8"SceneAOff");

    // check REMOVE
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_REMOVE, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaA", area->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());
  }
}

TEST_F(ResultAPI_viewaction, tc_03_dontMoveButReplace)
{
  // initialize
  arb_->clearArbitration();

  // Precondition
  // 	AreaA = WarnA
  // 	AreaB = WarnAB
  // Test
  // 	WarnA OFF
  // Expect
  // 	AreaA = WarnAB
  // 	AreaB = WarnAB
  // 	ViewAction = TRANSITION_REPLACE from WarnA to WarnAB @ AreaA
  {
    // Set Precondition
    result_ = arb_->execute(u8"WarnA");
    result_ = arb_->execute(u8"WarnAB");

    const std::list<const RBAArea*> visibleAreas = result_->getVisibleAreas();
    EXPECT_EQ(2u, visibleAreas.size());

    // Test
    result_ = arb_->execute(u8"WarnA", false);

    // Check Result
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_REPLACE, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaA", area->getName().c_str());
    const RBAViewContent* fcont = va->getFromContent();
    EXPECT_STREQ(u8"WarnA", fcont->getName().c_str());
    const RBAViewContent* tcont = va->getToContent();
    EXPECT_STREQ(u8"WarnAB", tcont->getName().c_str());
  }
}

TEST_F(ResultAPI_viewaction, tc_04_dontMoveButAdd)
{
  // initialize
  arb_->clearArbitration();

  // Precondition
  // 	AreaA = null
  // 	AreaB = WarnAB
  //	AreaC = WarnC
  //	WarnA is active but not displayed by Constraint "AreaC.isDisplayed() -> !WarnA.isVisible()"
  // Test
  // 	WarnA OFF
  // Expect
  // 	AreaA = WarnAB
  // 	AreaB = WarnAB
  //	AreaC = WarnC
  // 	ViewAction = TRANSITION_ADD WarnAB @ AreaA
  {
	// Set Precondition
	result_ = arb_->execute(u8"WarnA");
	result_ = arb_->execute(u8"WarnAB");
	result_ = arb_->execute(u8"WarnC");

	// Test
	result_ = arb_->execute(u8"WarnA", false);

	// Check Result
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    const RBAViewAction* va = viewActions.front();
    EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
    const RBAArea* area = va->getArea();
    EXPECT_STREQ(u8"AreaA", area->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"WarnAB", cont->getName().c_str());
  }
}
}

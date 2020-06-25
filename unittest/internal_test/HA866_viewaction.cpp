// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_viewaction.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA866_viewaction.hpp"

namespace resultapi {

using namespace rba;

/**
 * ViewActionテスト
 */
HA866_viewaction::HA866_viewaction()
{
}

HA866_viewaction::~HA866_viewaction()
{
}

void HA866_viewaction::SetUp()
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new rba::RBAArbitrator(model_);
}

void HA866_viewaction::TearDown()
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
}

TEST_F(HA866_viewaction, tc_01_forward)
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
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
    ASSERT_NE(nullptr, areaFrom);
    EXPECT_STREQ(u8"AreaA", areaFrom->getName().c_str());
    const RBAArea* areaTo = va->getToArea();
    EXPECT_STREQ(u8"AreaB", areaTo->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());

    // check method
    EXPECT_EQ(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_NE(nullptr, va->getFromArea());
    EXPECT_NE(nullptr, va->getToArea());
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_EQ(nullptr, va->getContent());
    EXPECT_NE(nullptr, va->getFromContent());
    EXPECT_NE(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
  }
}

TEST_F(HA866_viewaction, tc_02_revese)
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_EQ(nullptr, va->getContent());
    EXPECT_NE(nullptr, va->getFromContent());
    EXPECT_NE(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
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
    ASSERT_NE(nullptr, areaFrom);
    EXPECT_STREQ(u8"AreaB", areaFrom->getName().c_str());
    const RBAArea* areaTo = va->getToArea();
    EXPECT_STREQ(u8"AreaA", areaTo->getName().c_str());
    const RBAViewContent* cont = va->getContent();
    EXPECT_STREQ(u8"Content1", cont->getName().c_str());

    // check method
    EXPECT_EQ(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_NE(nullptr, va->getFromArea());
    EXPECT_NE(nullptr, va->getToArea());
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

    // check method
    EXPECT_NE(nullptr, va->getArea());
    EXPECT_NE(nullptr, va->getContent());
    EXPECT_EQ(nullptr, va->getFromContent());
    EXPECT_EQ(nullptr, va->getToContent());
    EXPECT_EQ(nullptr, va->getFromArea());
    EXPECT_EQ(nullptr, va->getToArea());
  }
}

}

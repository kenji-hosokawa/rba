// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA923_errorcheck.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA923_errorcheck.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA923_errorcheck::HA923_errorcheck()
{
}

HA923_errorcheck::~HA923_errorcheck()
{
}

void HA923_errorcheck::SetUp()
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new rba::RBAArbitrator(model_);
}

void HA923_errorcheck::TearDown()
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

TEST_F(HA923_errorcheck, unknown_content)
{
  // [EXEC] ContentA1 -> AreaA
  result_ = arb_->execute(u8"ContentA1");
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:Add
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(1u, actions.size());
    const RBAViewAction* va = actions.front();
    EXPECT_NE(nullptr, va);
    EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
  }

  // [EXEC] Unknown Content error
  result_ = arb_->execute(u8"UnknownContent");
  EXPECT_NE(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:nothing
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(0u, actions.size());
  }

  // [EXEC] no content
  result_ = arb_->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:nothing
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(0u, actions.size());
  }
}

TEST_F(HA923_errorcheck, unknown_scene)
{
  // [EXEC] ContentA1 -> AreaA
  result_ = arb_->execute(u8"ContentA1");
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:Add
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(1u, actions.size());
    const RBAViewAction* va = actions.front();
    EXPECT_NE(nullptr, va);
    EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
  }

  // [EXEC] Unknown Scene
  std::list<std::pair<std::string, std::int32_t>> properties;
  properties.push_back(std::make_pair("AAA", 10));
  properties.push_back(std::make_pair("BBB", 20));
  result_ = arb_->execute(u8"UnknownScene", properties);
  EXPECT_NE(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:nothing
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(0u, actions.size());
  }

  // [EXEC] no content
  result_ = arb_->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result_->getStatusType());

  // ViewAction:nothing
  {
    const std::list<const RBAViewAction*> actions = result_->getViewActions();
    EXPECT_EQ(0u, actions.size());
  }
}

}

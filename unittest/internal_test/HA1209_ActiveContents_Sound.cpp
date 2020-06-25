// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_ActiveContents_Sound.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA1209_ActiveContents_Sound.hpp"
#include "TestCommon.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAExpression.hpp"
#include "RBAArbitrator.hpp"
#include "RBAConstraintInfo.hpp"

namespace {

void HA1209_ActiveContents_Sound::SetUp()
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new rba::RBAArbitrator(model_);
}

void HA1209_ActiveContents_Sound::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

TEST_F(HA1209_ActiveContents_Sound, Test_1)
{
  auto A1 = arb_->getModel()->findZone(u8"A1");
  ASSERT_NE(nullptr, A1);
  auto A2 = arb_->getModel()->findZone(u8"A2");
  ASSERT_NE(nullptr, A2);
  auto A3 = arb_->getModel()->findZone(u8"A3");
  ASSERT_NE(nullptr, A3);
  
  // 実行 C1,C2,C4,C5/ON
  arb_->setContentState(u8"C1", true);
  arb_->setContentState(u8"C2", true);
  arb_->setContentState(u8"C4", true);
  auto result = arb_->execute(u8"C5", true);
  ASSERT_EQ(result->getStatusType(), rba::RBAResultStatusType::SUCCESS);

  // 期待値比較 A1 -> C2
  {
    EXPECT_TRUE(result->isSounding(A1));
    auto state = result->getContentState(A1);
    ASSERT_NE(nullptr, state);
    auto content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"C2", content->getName());
  }

  // 期待値比較 A2 -> mute
  {
    EXPECT_TRUE(result->isMute(A2));
  }

  // 期待値比較 A3 -> mute
  {
    EXPECT_TRUE(result->isMute(A3));
  }

  // 実行 C2/OFF
  result = arb_->execute(u8"C2", false);
  ASSERT_EQ(result->getStatusType(), rba::RBAResultStatusType::SUCCESS);

  // 期待値比較 A1 -> C1
  {
    EXPECT_TRUE(result->isSounding(A1));
    auto state = result->getContentState(A1);
    ASSERT_NE(nullptr, state);
    auto content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"C1", content->getName());
  }

  // 期待値比較 A2 -> mute
  {
    EXPECT_TRUE(result->isMute(A2));
  }

  // 期待値比較 A3 -> mute
  {
    EXPECT_TRUE(result->isMute(A3));
  }
}

}

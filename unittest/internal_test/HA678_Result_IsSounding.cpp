// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA678_Result_IsSounding.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA678_Result_IsSounding.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA678_Result_IsSounding::HA678_Result_IsSounding(void)
{
}

HA678_Result_IsSounding::~HA678_Result_IsSounding(void)
{
}

void HA678_Result_IsSounding::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA678_Result_IsSounding::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA678_Result_IsSounding, Test_1) {
  std::unique_ptr<RBAResult> result;
  const rba::RBASoundContentState* soundContentState = nullptr;

  soundContentState = arb->getModel()->findSoundContentState("C1/NORMAL");
  ASSERT_NE(nullptr, soundContentState);
  // NotSounding & NotSounding -> Sounding & Sounding
  // C1がCとDに割り当てられ、C,DがSoundingのとき、IsSoundingはtrue
  result = arb->execute("C1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isSounding(soundContentState));
  // Sounding & Sounding -> NotSounding & NotSounding
  // C1が取り下げられ、IsSoundingはfalse
  result = arb->execute("C1/NORMAL", false);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isSounding(soundContentState));

  soundContentState = arb->getModel()->findSoundContentState("A1/NORMAL");
  ASSERT_NE(nullptr, soundContentState);
  // NotSounding & NotSounding -> Sounding & Mute
  // A1がAとBに割り当てられ、AがSounding BがMuteのとき、IsSoundingはtrue
  result = arb->execute("A1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isSounding(soundContentState));
  // Sounding & Mute -> NotSounding & Mute
  // AにA2が割り当てられ、A1のIsSoundingはfalse
  result = arb->execute("A2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isSounding(soundContentState));

  soundContentState = arb->getModel()->findSoundContentState("E1/NORMAL");
  // NotSounding & NotSounding -> Mute & Sounding
  // E1がEとFに割り当てられ、EがMute FがSoundingのとき、IsSoundingはtrue
  result = arb->execute("E1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isSounding(soundContentState));
  // Mute & Sounding -> Mute & NotSounding
  // FにF1が割り当てられ、E1のIsSoundingはfalse
  result = arb->execute("F1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isSounding(soundContentState));
}
}

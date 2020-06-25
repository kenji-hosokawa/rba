// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA853_Result_CallAPI_IsActive.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA853_Result_CallAPI_IsActive.hpp"

namespace {

using namespace rba;

HA853_Result_CallAPI_IsActive::HA853_Result_CallAPI_IsActive() {}
HA853_Result_CallAPI_IsActive::~HA853_Result_CallAPI_IsActive() {}

void HA853_Result_CallAPI_IsActive::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA853_Result_CallAPI_IsActive::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

TEST_F(HA853_Result_CallAPI_IsActive, Test_01)
{
  const RBAViewContent* vc1 = model_->findViewContent(u8"ViewA1");
  const RBAViewContent* vc2 = model_->findViewContent(u8"ViewB1");
  const RBAViewContent* vc3 = model_->findViewContent(u8"ViewC1");
  const RBASoundContent* sc1 = model_->findSoundContent(u8"SoundA1");
  const RBASoundContent* sc2 = model_->findSoundContent(u8"SoundB1");
  const RBASoundContent* sc3 = model_->findSoundContent(u8"SoundC1");
  result_ = arb_->execute();
  EXPECT_FALSE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_FALSE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewA1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_FALSE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewB1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_FALSE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewC1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundA1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundB1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_TRUE(result_->isActive(sc2));
  EXPECT_FALSE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundC1/NORMAL", true);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_TRUE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewB1/NORMAL", false);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_TRUE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundB1/NORMAL", false);
  EXPECT_TRUE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewA1/NORMAL", false);
  EXPECT_FALSE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_TRUE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundA1/NORMAL", false);
  EXPECT_FALSE(result_->isActive(vc1));
  EXPECT_FALSE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"ViewB1/EXTENDED", true);
  EXPECT_FALSE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_FALSE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
  result_ = arb_->execute(u8"SoundB1/EXTENDED", true);
  EXPECT_FALSE(result_->isActive(vc1));
  EXPECT_TRUE(result_->isActive(vc2));
  EXPECT_TRUE(result_->isActive(vc3));
  EXPECT_FALSE(result_->isActive(sc1));
  EXPECT_TRUE(result_->isActive(sc2));
  EXPECT_TRUE(result_->isActive(sc3));
}

}

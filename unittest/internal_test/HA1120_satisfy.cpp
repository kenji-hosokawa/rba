// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1120_satisfy.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1120_satisfy.hpp"

namespace {

using namespace rba;

HA1120_satisfy::HA1120_satisfy() {}
HA1120_satisfy::~HA1120_satisfy() {}

void HA1120_satisfy::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1120_satisfy::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1120_satisfy::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1120_satisfy::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

TEST_F(HA1120_satisfy, test)
{
  arb_->clearArbitration();
  result_ = arb_->execute(u8"IGオン", true);
  EXPECT_FALSE(isSuccess(""));
  EXPECT_FALSE(isSatisfiedConstraints(""));

  result_ = arb_->execute(u8"ContentA/NORMAL");
  EXPECT_TRUE(isSuccess(""));
  EXPECT_TRUE(isSatisfiedConstraints(""));

  result_ = arb_->execute(u8"IGオン", true);
  EXPECT_FALSE(isSuccess(""));
  EXPECT_FALSE(isSatisfiedConstraints(""));
}

}

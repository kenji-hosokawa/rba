// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Result_CallInternalAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Result_CallInternalAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Result_CallInternalAPI::HA497_Result_CallInternalAPI(void)
{
}

HA497_Result_CallInternalAPI::~HA497_Result_CallInternalAPI(void)
{
}

void HA497_Result_CallInternalAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Result_CallInternalAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_Result_CallInternalAPI, getLog) {
  std::unique_ptr<RBAResult> result;
  std::string log;
  result = arb->execute();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  log = result->getLog();
}

}

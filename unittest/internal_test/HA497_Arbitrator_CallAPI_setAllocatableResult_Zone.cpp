// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Arbitrator_CallAPI_setAllocatableResult_Zone.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Arbitrator_CallAPI_setAllocatableResult_Zone.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Arbitrator_CallAPI_setAllocatableResult_Zone::HA497_Arbitrator_CallAPI_setAllocatableResult_Zone(void)
{
}

HA497_Arbitrator_CallAPI_setAllocatableResult_Zone::~HA497_Arbitrator_CallAPI_setAllocatableResult_Zone(void)
{
}

void HA497_Arbitrator_CallAPI_setAllocatableResult_Zone::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Arbitrator_CallAPI_setAllocatableResult_Zone::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_Arbitrator_CallAPI_setAllocatableResult_Zone, test_1) {
  const rba::RBAZone* zone = arb->getModel()->findZone(u8"A");
  const rba::RBASoundContentState* state = arb->getModel()->findSoundContentState(u8"A1/NORMAL");

  // 初期値が非表示の確認
  std::unique_ptr<RBAResult> result;
  result = arb->execute();
  EXPECT_FALSE(result->isSounding(zone));
  EXPECT_FALSE(result->isSounding(state));

  // setAllocatableResultで調停結果が変わることの確認
  bool res = arb->setAllocatableResult("A", "A1/NORMAL");
  ASSERT_TRUE(res);
  result = arb->execute();
  EXPECT_TRUE(result->isSounding(zone));
  EXPECT_TRUE(result->isSounding(state));
}
}

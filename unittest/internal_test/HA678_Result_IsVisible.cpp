// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA678_Result_IsVisible.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA678_Result_IsVisible.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA678_Result_IsVisible::HA678_Result_IsVisible(void)
{
}

HA678_Result_IsVisible::~HA678_Result_IsVisible(void)
{
}

void HA678_Result_IsVisible::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA678_Result_IsVisible::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA678_Result_IsVisible, Test_1) {
  std::unique_ptr<RBAResult> result;
  const rba::RBAViewContentState* viewContentState = nullptr;

  viewContentState = arb->getModel()->findViewContentState("C1/NORMAL");
  ASSERT_NE(nullptr, viewContentState);
  // NotVisible & NotVisible -> Visible & Visible
  // C1がCとDに割り当てられ、C,DがVisibleのとき、IsVisibleはtrue
  result = arb->execute("C1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isVisible(viewContentState));
  // Visible & Visible -> NotVisible & NotVisible
  // C1が取り下げられ、IsVisibleはfalse
  result = arb->execute("C1/NORMAL", false);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isVisible(viewContentState));

  viewContentState = arb->getModel()->findViewContentState("A1/NORMAL");
  ASSERT_NE(nullptr, viewContentState);
  // NotVisible & NotVisible -> Visible & Hidden
  // A1がAとBに割り当てられ、AがVisible BがHiddenのとき、IsVisibleはtrue
  result = arb->execute("A1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isVisible(viewContentState));
  // Visible & Hidden -> NotVisible & Hidden
  // AにA2が割り当てられ、A1のIsVisibleはfalse
  result = arb->execute("A2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isVisible(viewContentState));

  viewContentState = arb->getModel()->findViewContentState("E1/NORMAL");
  // NotVisible & NotVisible -> Hidden & Visible
  // E1がEとFに割り当てられ、EがHidden FがVisibleのとき、IsVisibleはtrue
  result = arb->execute("E1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_TRUE(result->isVisible(viewContentState));
  // Hidden & Visible -> Hidden & NotVisible
  // FにF1が割り当てられ、E1のIsVisibleはfalse
  result = arb->execute("F1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  EXPECT_FALSE(result->isVisible(viewContentState));

}

}

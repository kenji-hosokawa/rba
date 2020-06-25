// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * TestCancelarbitration.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA457_CancelArbitration.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA457_CancelArbitration::HA457_CancelArbitration(void)
{
}

HA457_CancelArbitration::~HA457_CancelArbitration(void)
{
}

void HA457_CancelArbitration::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA457_CancelArbitration::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

bool isActive(const std::list<const RBAViewContentState*>& states, std::string& context)
{
  for(const RBAViewContentState* state : states) {
    if(state->getUniqueName() == context) {
      return true;
    }
  }

  return false;
}

TEST_F(HA457_CancelArbitration, Test_01_success)
{
  // execute -> res0
  std::string contextA2 = u8"コンテンツA2/NORMAL";
  std::unique_ptr<RBAResult> res0 = arb->execute(contextA2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res0->getStatusType());
  EXPECT_TRUE(isActive(res0->getActiveViewContentStates(), contextA2));

  // cancel -> res1
  std::unique_ptr<RBAResult> res1 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res1->getStatusType());
  EXPECT_FALSE(isActive(res1->getActiveViewContentStates(), contextA2));

  // execute -> res2
  //std::string contextA2 = u8"コンテンツA2/NORMAL";
  std::unique_ptr<RBAResult> res2 = arb->execute(contextA2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res2->getStatusType());
  EXPECT_TRUE(isActive(res2->getActiveViewContentStates(), contextA2));

  // execute -> res3
  std::string contextB2 = u8"コンテンツB2/NORMAL";
  std::unique_ptr<RBAResult> res3 = arb->execute(contextB2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res3->getStatusType());
  EXPECT_TRUE(isActive(res3->getActiveViewContentStates(), contextB2));

  std::string areaNameC = u8"エリアC";
  const rba::RBAArea* areaC = arb->getModel()->findArea(areaNameC);
  ASSERT_NE(nullptr, areaC);
  EXPECT_FALSE(res3->isVisible(areaC));

  // execute -> res4
  std::string contextC2 = u8"コンテンツC2/NORMAL";
  std::unique_ptr<RBAResult> res4 = arb->execute(contextC2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res4->getStatusType());
  EXPECT_TRUE(isActive(res4->getActiveViewContentStates(), contextC2));
  EXPECT_TRUE(res4->isVisible(areaC));

  // cancel -> res5
  std::unique_ptr<RBAResult> res5 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res5->getStatusType());
  EXPECT_FALSE(isActive(res5->getActiveViewContentStates(), contextC2));
  EXPECT_FALSE(res5->isVisible(areaC));

  // execute -> res6
  //std::string contextC2 = u8"コンテンツC2/NORMAL";
  std::unique_ptr<RBAResult> res6 = arb->execute(contextC2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res6->getStatusType());
  EXPECT_TRUE(isActive(res6->getActiveViewContentStates(), contextC2));
  EXPECT_TRUE(res6->isVisible(areaC));

  // execute -> res7
  //std::string contextC2 = u8"コンテンツC2/NORMAL";
  std::unique_ptr<RBAResult> res7 = arb->execute(contextC2, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res7->getStatusType());
  EXPECT_TRUE(isActive(res7->getActiveViewContentStates(), contextC2));
  EXPECT_TRUE(res6->isVisible(areaC));

  // cancel -> res8
  std::unique_ptr<RBAResult> res8 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res8->getStatusType());
  EXPECT_TRUE(isActive(res8->getActiveViewContentStates(), contextC2));
  EXPECT_TRUE(res8->isVisible(areaC));

}

TEST_F(HA457_CancelArbitration, Test_02_noexecute)
{
  // cancel -> res0
  std::unique_ptr<RBAResult> res0 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::CANCEL_ERROR, res0->getStatusType());
}

TEST_F(HA457_CancelArbitration, Test_03_continuously)
{
  // execute -> res0
  std::string context = u8"コンテンツA2/NORMAL";
  std::unique_ptr<RBAResult> res0 = arb->execute(context, true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res0->getStatusType());
  EXPECT_TRUE(isActive(res0->getActiveViewContentStates(), context));

  // cancel -> res1
  std::unique_ptr<RBAResult> res1 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, res1->getStatusType());

  // cancel -> res2
  std::unique_ptr<RBAResult> res2 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::CANCEL_ERROR, res2->getStatusType());

  // cancel -> res3
  std::unique_ptr<RBAResult> res3 = arb->cancelArbitration();
  EXPECT_EQ(rba::RBAResultStatusType::CANCEL_ERROR, res3->getStatusType());
}

}

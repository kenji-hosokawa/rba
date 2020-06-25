// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetResultContentState_AreaZoneConstraint.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA493_SetResultContentState_AreaZoneConstraint.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA493_SetResultContentState_AreaZoneConstraint::HA493_SetResultContentState_AreaZoneConstraint(void)
{
}

HA493_SetResultContentState_AreaZoneConstraint::~HA493_SetResultContentState_AreaZoneConstraint(void)
{
}

void HA493_SetResultContentState_AreaZoneConstraint::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA493_SetResultContentState_AreaZoneConstraint::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_04)
{
  // A2=ON -> A2割り当て　でA2に差し替え
  std::string areaName = u8"エリアA";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    std::string context = u8"表示コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"表示コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(areaName, contextSet);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isHidden(area));  // エリアA hidden
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_05)
{
  // A2=ON -> A2割り当て　でA0に差し替え
  std::string areaName = u8"エリアA";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    std::string context = u8"表示コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"表示コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(areaName, contextSet);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isHidden(area));  // エリアA hidden
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_06)
{
  // A2=ON -> A2割り当て　でB1に差し替え
  std::string areaName = u8"エリアA";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    std::string context = u8"表示コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"表示コンテンツB1/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(areaName, contextSet);
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isHidden(area));  // エリアA hidden
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_07)
{
  // A1=OFF でA0に差し替え
  std::string areaName = u8"エリアA";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    std::string context = u8"表示コンテンツA1/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, false);
    EXPECT_FALSE(result->isVisible(area));
  }
  {
    std::string contextSet = u8"表示コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(areaName, contextSet);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_08)
{
  // A1=OFF でA0に差し替え
  std::string areaName = u8"エリアA";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    std::string context = u8"表示コンテンツA1/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, false);
    EXPECT_FALSE(result->isVisible(area));
  }
  {
    std::string contextSet = u8"表示コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(areaName, contextSet);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_12)
{
  // A2=ON -> A2割り当て　でA2に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"音コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isMute(zone));  // ゾーンA mute
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_13)
{
  // A2=ON -> A2割り当て　でA0に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"音コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isMute(zone));  // ゾーンA mute
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_14)
{
  // A2=ON -> A2割り当て　でB1に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA2/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    std::string contextSet = u8"音コンテンツB1/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isMute(zone));  // ゾーンA mute
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_15)
{
  // A3=ON -> A3割り当て　でA3に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA3/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
  {
    std::string contextSet = u8"音コンテンツA3/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_16)
{
  // A3=ON -> A3割り当て　でA0に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA3/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
  {
    std::string contextSet = u8"音コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_17)
{
  // A3=ON -> A3割り当て　でB1に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA3/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
  {
    std::string contextSet = u8"音コンテンツB1/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    EXPECT_TRUE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_NE(nullptr, state);
    EXPECT_STREQ(contextSet.c_str(), state->getUniqueName().c_str());
    EXPECT_TRUE(result->isAttenuated(zone));  // ゾーンA attenuated
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_18)
{
  // A1=OFF　でA0に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA1/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, false);
    EXPECT_FALSE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_EQ(nullptr, state);
  }
  {
    std::string contextSet = u8"音コンテンツA0/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    EXPECT_TRUE(result->isSounding(zone));
  }
}

TEST_F(HA493_SetResultContentState_AreaZoneConstraint, Test_19)
{
  // A1=OFF　でB1に差し替え
  std::string zoneName = u8"ゾーンA";
  const rba::RBAZone* zone = arb->getModel()->findZone(zoneName);
  ASSERT_NE(nullptr, zone);
  {
    std::string context = u8"音コンテンツA1/NORMAL";
    std::unique_ptr<RBAResult> result = arb->execute(context, false);
    EXPECT_FALSE(result->isSounding(zone));
    const rba::RBASoundContentState* state = result->getContentState(zone);
    ASSERT_EQ(nullptr, state);
  }
  {
    std::string contextSet = u8"音コンテンツB1/NORMAL";
    std::unique_ptr<RBAResult> result
      = arb->setResultContentState(zoneName, contextSet);
    EXPECT_TRUE(result->isSounding(zone));
  }
}

}

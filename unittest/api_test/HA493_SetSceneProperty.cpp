// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetSceneProperty.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA493_SetSceneProperty.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA493_SetSceneProperty::HA493_SetSceneProperty(void)
{
}

HA493_SetSceneProperty::~HA493_SetSceneProperty(void)
{
}

void HA493_SetSceneProperty::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA493_SetSceneProperty::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA493_SetSceneProperty, Test_1)
{
  std::string areaName = u8"A1";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    // V1/N=0N
    std::string context = u8"V1/N";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    // GlobalWithProperty=ON, PropertyA=10 => hidden area
    std::string context = u8"GlobalWithProperty";
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair("PropertyA", 10));
    std::unique_ptr<RBAResult> result = arb->execute(context, props);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_FALSE(result->isVisible(area));
    EXPECT_TRUE(result->isHidden(area));
  }
}

TEST_F(HA493_SetSceneProperty, Test_2)
{
  std::string areaName = u8"A1";
  const rba::RBAArea* area = arb->getModel()->findArea(areaName);
  {
    // V1/N=0N
    std::string context = u8"V1/N";
    std::unique_ptr<RBAResult> result = arb->execute(context, true);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    EXPECT_STREQ(context.c_str(), state->getUniqueName().c_str());
  }
  {
    // GlobalWithProperty=ON, PropertyB=1 => no effect
    std::string context = u8"GlobalWithProperty";
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair("PropertyB", 1));
    std::unique_ptr<RBAResult> result = arb->execute(context, props);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_TRUE(result->isVisible(area));
    EXPECT_FALSE(result->isHidden(area));
  }
  {
    // GlobalWithProperty=ON, PropertyA=4 => no effect
    std::string context = u8"GlobalWithProperty";
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair("PropertyA", 4));
    std::unique_ptr<RBAResult> result = arb->execute(context, props);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_TRUE(result->isVisible(area));
    EXPECT_FALSE(result->isHidden(area));
  }
  {
    // GlobalWithProperty=ON, PropertyA=10 => hidden area
    std::string context = u8"GlobalWithProperty";
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair("PropertyA", 10));
    std::unique_ptr<RBAResult> result = arb->execute(context, props);
    ASSERT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
    EXPECT_FALSE(result->isVisible(area));
    EXPECT_TRUE(result->isHidden(area));
  }
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA672_getprop.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA672_getprop.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA672_getprop::HA672_getprop(void)
{
}

HA672_getprop::~HA672_getprop(void)
{
}

void HA672_getprop::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA672_getprop::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA672_getprop, prop)
{
  std::unique_ptr<RBAResult> result;
  // 初期化処理
  std::string ringAreaName = u8"リングエリア";
  const rba::RBAArea* ringArea = arb->getModel()->findArea(ringAreaName);
  ASSERT_NE(nullptr, ringArea);

  // REG/NORMALで調停実行
  {
    result = arb->execute(u8"REG/NORMAL", true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // この時点ではリングエリア=REG/NORMAL で hiddenではない
  {
    EXPECT_TRUE(result->isVisible(ringArea));
    const rba::RBAViewContentState* state = result->getContentState(ringArea);
    const rba::RBAViewContent* content = state->getOwner();
    EXPECT_STREQ(u8"REG", content->getName().c_str());
    EXPECT_FALSE(result->isHidden(ringArea));
  }

  // Hoge::poge=1で調停実行
  {
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair(u8"poge", 1));
    result = arb->execute(u8"Hoge", props);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // この時点ではリングエリア=REG/NORMAL で hiddenではない
  {
    EXPECT_TRUE(result->isVisible(ringArea));
    const rba::RBAViewContentState* state = result->getContentState(ringArea);
    const rba::RBAViewContent* content = state->getOwner();
    EXPECT_STREQ(u8"REG", content->getName().c_str());
    EXPECT_FALSE(result->isHidden(ringArea));
  }

  // Hoge::poge=0で調停実行
  {
    std::list<std::pair<std::string, std::int32_t>> props;
    props.push_back(std::make_pair(u8"poge", 0));
    result = arb->execute(u8"Hoge", props);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // リングエリア=REG/NORMAL で hiddenになる
  {
    EXPECT_FALSE(result->isVisible(ringArea));
    const rba::RBAViewContentState* state = result->getContentState(ringArea);
    const rba::RBAViewContent* content = state->getOwner();
    EXPECT_STREQ(u8"REG", content->getName().c_str());
    EXPECT_TRUE(result->isHidden(ringArea));
  }

}

}

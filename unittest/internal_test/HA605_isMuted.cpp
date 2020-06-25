// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA605_isMuted.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA605_isMuted.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA605_isMuted::HA605_isMuted(void)
{
}

HA605_isMuted::~HA605_isMuted(void)
{
}

void HA605_isMuted::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA605_isMuted::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA605_isMuted, Test_getViewContentState) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = { u8"C",u8"ON",u8"外気温",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  const rba::RBAArea* area1 = arb->getModel()->findArea(u8"外気温エリア");
  ASSERT_NE(nullptr, area1);
  EXPECT_TRUE(result->isVisible(area1));
  const RBAViewContentState* content1 = result->getViewContentState(area1);
  ASSERT_NE(nullptr, content1);
  EXPECT_EQ(u8"外気温/NORMAL",content1->getUniqueName());

  const rba::RBAArea* area2 = arb->getModel()->findArea(u8"HUD_外気温エリア");
  ASSERT_NE(nullptr, area2);
  EXPECT_FALSE(result->isVisible(area2));
  const RBAViewContentState* content2 = result->getViewContentState(area2);
  ASSERT_NE(nullptr, content2); // 改修前はここでfalseしていた
  EXPECT_EQ(u8"外気温/NORMAL",content2->getUniqueName());
}
TEST_F(HA605_isMuted, Test_getSoundContentState) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"警告音",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }
  const rba::RBAZone* zone = arb->getModel()->findZone(u8"メインスピーカー");
  ASSERT_NE(nullptr, zone);
  EXPECT_FALSE(result->isSounding(zone));
  const RBASoundContentState* content = result->getSoundContentState(zone);
  ASSERT_NE(nullptr, content); // 改修前はここでfalseしていた
  EXPECT_EQ(u8"警告音/NORMAL",content->getUniqueName());
}

}

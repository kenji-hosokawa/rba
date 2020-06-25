// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Zone_CallAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Zone_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Zone_CallAPI::HA497_Zone_CallAPI(void)
{
}

HA497_Zone_CallAPI::~HA497_Zone_CallAPI(void)
{
}

void HA497_Zone_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Zone_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_Zone_CallAPI, getPriority) {
  std::int32_t priority;
  priority = model->findZone(u8"A")->getPriority();
  EXPECT_EQ(100,priority);
  priority = model->findZone(u8"B")->getPriority();
  EXPECT_EQ(0,priority);
  priority = model->findZone(u8"C")->getPriority();
  EXPECT_EQ(-100,priority);
}
TEST_F(HA497_Zone_CallAPI, getContents) {
  std::list<const RBASoundContent*> cList;
  cList = (std::list<const RBASoundContent*>&)model->findZone(u8"A")->getContents();
  ASSERT_EQ(1U,cList.size());
  EXPECT_NE(std::find(cList.begin(),cList.end(),model->findSoundContent(u8"A1")),cList.end());
  cList = (std::list<const RBASoundContent*>&)model->findZone(u8"B")->getContents();
  ASSERT_EQ(2U,cList.size());
  EXPECT_NE(std::find(cList.begin(),cList.end(),model->findSoundContent(u8"B1")),cList.end());
  EXPECT_NE(std::find(cList.begin(),cList.end(),model->findSoundContent(u8"B2")),cList.end());
  cList = (std::list<const RBASoundContent*>&)model->findZone(u8"C")->getContents();
  ASSERT_EQ(0U,cList.size());
}
}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Display_CallAPI.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Display_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Display_CallAPI::HA497_Display_CallAPI(void)
{
}

HA497_Display_CallAPI::~HA497_Display_CallAPI(void)
{
}

void HA497_Display_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Display_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}
TEST_F(HA497_Display_CallAPI, getSize) {
  const std::list<const RBADisplay*>dList = model->getDisplays();
  ASSERT_EQ(dList.size(),3U);
  const RBADisplay* da = model->findDisplay(u8"DisplayA");
  ASSERT_NE(da,nullptr);
  const RBADisplay* db = model->findDisplay(u8"DisplayB");
  ASSERT_NE(db,nullptr);
  const RBADisplay* dc = model->findDisplay(u8"DisplayC");
  ASSERT_NE(dc,nullptr);
  const RBASize* daSize = da->getSize();
  const RBASize* dbSize = db->getSize();
  const RBASize* dcSize = dc->getSize();
  EXPECT_EQ(daSize->getName(),u8"Default1");
  EXPECT_EQ(dbSize->getName(),u8"Default2");
  EXPECT_EQ(dcSize->getName(),u8"Default3");
  EXPECT_EQ(daSize->getWidth(),0);
  EXPECT_EQ(dbSize->getWidth(),10000);
  EXPECT_EQ(dcSize->getWidth(),-100);
  EXPECT_EQ(daSize->getHeight(),0);
  EXPECT_EQ(dbSize->getHeight(),20000);
  EXPECT_EQ(dcSize->getHeight(),-200);
}
TEST_F(HA497_Display_CallAPI, getAreas) {
  const std::list<const RBADisplay*>dList = model->getDisplays();
  ASSERT_EQ(dList.size(),3U);
  const RBADisplay* da = model->findDisplay(u8"DisplayA");
  ASSERT_NE(da,nullptr);
  const RBADisplay* db = model->findDisplay(u8"DisplayB");
  ASSERT_NE(db,nullptr);
  const RBADisplay* dc = model->findDisplay(u8"DisplayC");
  ASSERT_NE(dc,nullptr);
  const std::list<const RBAArea*> daList = da->getAreas();
  const std::list<const RBAArea*> dbList = db->getAreas();
  const std::list<const RBAArea*> dcList = dc->getAreas();
  ASSERT_EQ(daList.size(),1U);
  ASSERT_EQ(dbList.size(),2U);
  ASSERT_EQ(dcList.size(),1U);
  EXPECT_NE(std::find(daList.begin(),daList.end(),model->findArea(u8"A")),daList.end());
  EXPECT_NE(std::find(dbList.begin(),dbList.end(),model->findArea(u8"B")),dbList.end());
  EXPECT_NE(std::find(dbList.begin(),dbList.end(),model->findArea(u8"C")),dbList.end());
  EXPECT_NE(std::find(dcList.begin(),dcList.end(),model->findArea(u8"C")),dcList.end());
}
}

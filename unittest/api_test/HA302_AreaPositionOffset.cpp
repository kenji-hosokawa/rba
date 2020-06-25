// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA302_AreaPositionOffset.cpp
 */

#include <iostream>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA302_AreaPositionOffset.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA302_AreaPositionOffset::HA302_AreaPositionOffset(void)
{
}

HA302_AreaPositionOffset::~HA302_AreaPositionOffset(void)
{
}

void HA302_AreaPositionOffset::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA302_AreaPositionOffset::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

const RBAArea*
getArea(RBAResult* result, std::string areaName)
{
  for(const RBAArea* area : result->getVisibleAreas()) {
    if(area->getName() == areaName) {
      return area;
    }
  }
  for(const RBAArea* area : result->getInvisibleAreas()) {
    if(area->getName() == areaName) {
      return area;
    }
  }

  return nullptr;
}

TEST_F(HA302_AreaPositionOffset, Test_01_default_notactive)
{
  // Input
  std::string context = u8"Content01/NORMAL";
  bool request = false;
  // Expect
  std::string expAreaName = u8"AreaA";
  // std::string expSizeName = u8"Size01";
  std::int32_t expX = 100;
  std::int32_t expY = 200;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_EQ(nullptr, sizeObj);

  // EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_02_default_active)
{
  // Input
  std::string context = u8"Content01/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size01";
  std::int32_t expX = 100;
  std::int32_t expY = 200;


  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_03_size02)
{
  // Input
  std::string context = u8"Content02/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size02";
  std::int32_t expX = 111;
  std::int32_t expY = 212;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_04_size03)
{
  // Input
  std::string context = u8"Content03/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size03";
  std::int32_t expX = 112;
  std::int32_t expY = 213;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_05_size04)
{
  // Input
  std::string context = u8"Content04/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size04";
  std::int32_t expX = 113;
  std::int32_t expY = 214;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_06_size05)
{
  // Input
  std::string context = u8"Content05/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size05";
  std::int32_t expX = 114;
  std::int32_t expY = 215;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_07_size06)
{
  // Input
  std::string context = u8"Content06/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size06";
  std::int32_t expX = 115;
  std::int32_t expY = 216;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_08_size07)
{
  // Input
  std::string context = u8"Content07/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size07";
  std::int32_t expX = 116;
  std::int32_t expY = 217;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_09_size08)
{
  // Input
  std::string context = u8"Content08/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size08";
  std::int32_t expX = 117;
  std::int32_t expY = 218;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_10_size09)
{
  // Input
  std::string context = u8"Content09/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size09";
  std::int32_t expX = 118;
  std::int32_t expY = 219;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_11_size10)
{
  // Input
  std::string context = u8"Content10/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaA";
  std::string expSizeName = u8"Size10";
  std::int32_t expX = 119;
  std::int32_t expY = 220;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_12_CENTER_BOTTOM)
{
  // Input
  std::string context = u8"Content02/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaB";
  std::string expSizeName = u8"Size02";
  std::int32_t expX = 121;
  std::int32_t expY = 132;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_13_CENTER_MIDDLE)
{
  // Input
  std::string context = u8"Content03/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaC";
  std::string expSizeName = u8"Size03";
  std::int32_t expX = 132;
  std::int32_t expY = 143;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_14_CENTER_TOP)
{
  // Input
  std::string context = u8"Content04/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaD";
  std::string expSizeName = u8"Size04";
  std::int32_t expX = 143;
  std::int32_t expY = 154;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_15_LEFT_BOTTOM)
{
  // Input
  std::string context = u8"Content05/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaE";
  std::string expSizeName = u8"Size05";
  std::int32_t expX = 154;
  std::int32_t expY = 165;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_16_LEFT_MIDDLE)
{
  // Input
  std::string context = u8"Content06/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaF";
  std::string expSizeName = u8"Size06";
  std::int32_t expX = 165;
  std::int32_t expY = 176;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_17_LEFT_TOP)
{
  // Input
  std::string context = u8"Content07/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaG";
  std::string expSizeName = u8"Size07";
  std::int32_t expX = 176;
  std::int32_t expY = 187;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_18_RIGHT_BOTTOM)
{
  // Input
  std::string context = u8"Content08/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaH";
  std::string expSizeName = u8"Size08";
  std::int32_t expX = 187;
  std::int32_t expY = 198;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_19_RIGHT_MIDDLE)
{
  // Input
  std::string context = u8"Content09/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaI";
  std::string expSizeName = u8"Size09";
  std::int32_t expX = 198;
  std::int32_t expY = 209;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

TEST_F(HA302_AreaPositionOffset, Test_20_RIGHT_TOP)
{
  // Input
  std::string context = u8"Content10/NORMAL";
  bool request = true;
  // Expect
  std::string expAreaName = u8"AreaJ";
  std::string expSizeName = u8"Size10";
  std::int32_t expX = 209;
  std::int32_t expY = 220;

  std::unique_ptr<RBAResult> result = arb->execute(context, request);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  const RBAArea* area = getArea(result.get(), expAreaName);
  ASSERT_NE(nullptr, area);
  const RBASize* sizeObj = result->getSize(area);
  ASSERT_NE(nullptr, sizeObj);

  EXPECT_STREQ(expSizeName.c_str(), sizeObj->getName().c_str());
  EXPECT_EQ(expX, area->getX());
  EXPECT_EQ(expY, area->getY());
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA758_getArbitrationPolicy.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA758_getArbitrationPolicy.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

using namespace rba;

HA758_getArbitrationPolicy::HA758_getArbitrationPolicy(void)
{
}

HA758_getArbitrationPolicy::~HA758_getArbitrationPolicy(void)
{
}

void HA758_getArbitrationPolicy::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA758_getArbitrationPolicy::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA758_getArbitrationPolicy, Test_1) {
  RBAModel* mo = dynamic_cast<rba::RBAModelImpl*>((rba::RBAModel*)arb->getModel());
  {
    const RBAArea* area = mo->findArea(u8"A");
    RBAArbitrationPolicy policy = area->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::DEFAULT, policy);
  }
  {
    const RBAArea* area = mo->findArea(u8"B");
    RBAArbitrationPolicy policy = area->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::FIRST_COME_FIRST, policy);
  }
  {
    const RBAArea* area = mo->findArea(u8"C");
    RBAArbitrationPolicy policy = area->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::LAST_COME_FIRST, policy);
  }
  {
    const RBAArea* area = mo->findArea(u8"D");
    RBAArbitrationPolicy policy = area->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST, policy);
  }
  {
    const RBAArea* area = mo->findArea(u8"E");
    RBAArbitrationPolicy policy = area->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST, policy);
  }
  {
    const RBAZone* zone = mo->findZone(u8"AA");
    RBAArbitrationPolicy policy = zone->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::DEFAULT, policy);
  }
  {
    const RBAZone* zone = mo->findZone(u8"BB");
    RBAArbitrationPolicy policy = zone->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::FIRST_COME_FIRST, policy);
  }
  {
    const RBAZone* zone = mo->findZone(u8"CC");
    RBAArbitrationPolicy policy = zone->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::LAST_COME_FIRST, policy);
  }
  {
    const RBAZone* zone = mo->findZone(u8"DD");
    RBAArbitrationPolicy policy = zone->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST, policy);
  }
  {
    const RBAZone* zone = mo->findZone(u8"EE");
    RBAArbitrationPolicy policy = zone->getArbitrationPolicy();
    EXPECT_EQ(rba::RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST, policy);
  }
}

}

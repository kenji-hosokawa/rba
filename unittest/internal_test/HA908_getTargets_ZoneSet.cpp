// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA908_getTargets_ZoneSet.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA908_getTargets_ZoneSet.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

using namespace rba;

HA908_getTargets_ZoneSet::HA908_getTargets_ZoneSet(void)
{
}

HA908_getTargets_ZoneSet::~HA908_getTargets_ZoneSet(void)
{
}

void HA908_getTargets_ZoneSet::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA908_getTargets_ZoneSet::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA908_getTargets_ZoneSet, Test_1) {
  rba::RBAModelImpl* model1 = dynamic_cast<RBAModelImpl*>(const_cast<RBAModel*>(arb->getModel()));
  const std::list<const RBAZoneSet*> zoneSets = model1->getZoneSets();
  ASSERT_EQ(zoneSets.size(), 1U);
  const rba::RBAZoneSet* zoneSet = zoneSets.front();
  const std::list<const rba::RBAZone*> zones = zoneSet->getTargets();
  ASSERT_EQ(zones.size(), 2U);
  const rba::RBAZone* zone1 = zones.front();
  std::string name1 = zone1->getName();
  EXPECT_EQ(name1,"A");
  const rba::RBAZone* zone2 = zones.back();
  std::string name2 = zone2->getName();
  EXPECT_EQ(name2,"B");
}

}

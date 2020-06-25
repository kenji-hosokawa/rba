// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getTargets_AreaSet.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_getTargets_AreaSet.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

using namespace rba;

HA497_getTargets_AreaSet::HA497_getTargets_AreaSet(void)
{
}

HA497_getTargets_AreaSet::~HA497_getTargets_AreaSet(void)
{
}

void HA497_getTargets_AreaSet::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_getTargets_AreaSet::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_getTargets_AreaSet, Test_1) {
  rba::RBAModelImpl* model1 = dynamic_cast<RBAModelImpl*>((RBAModel*)arb->getModel());
  const std::list<const rba::RBAAreaSet*> areasets = model1->getAreaSets();
  ASSERT_EQ(areasets.size(), 1U);
  const rba::RBAAreaSet* areaset = areasets.front();
  const std::list<const rba::RBAArea*> areas = areaset->getTargets();
  ASSERT_EQ(areas.size(), 2U);
  const rba::RBAArea* area1 = areas.front();
  std::string name1 = area1->getName();
  EXPECT_EQ(name1,"A");
  const rba::RBAArea* area2 = areas.back();
  std::string name2 = area2->getName();
  EXPECT_EQ(name2,"B");
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getContents_Area.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_getContents_Area.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_getContents_Area::HA497_getContents_Area(void)
{
}

HA497_getContents_Area::~HA497_getContents_Area(void)
{
}

void HA497_getContents_Area::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_getContents_Area::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_getContents_Area, Test_1) {
  const rba::RBAModel* model1 = arb->getModel();
  const rba::RBAArea* area1 = model1->findArea("A");
  std::list<const rba::RBAViewContent*> contents = area1->getContents();
  ASSERT_EQ(contents.size(), 2U);
  const rba::RBAViewContent* content1 = contents.front();
  std::string name1 = content1->getName();
  EXPECT_EQ(name1,"A1");
  const rba::RBAViewContent* content2 = contents.back();
  EXPECT_EQ(content2->getName(),"B1");
}

}

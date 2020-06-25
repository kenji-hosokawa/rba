// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getSizes.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_getSizes.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_getSizes::HA497_getSizes(void)
{
}

HA497_getSizes::~HA497_getSizes(void)
{
}

void HA497_getSizes::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_getSizes::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_getSizes, Test_1) {
  const rba::RBAModel* model1 = arb->getModel();
  const rba::RBAArea* area1 = model1->findArea(u8"A");
  const std::list<const rba::RBASize*>sizes = area1->getSizes();
  ASSERT_EQ(sizes.size(), 2U);
  const rba::RBASize* size1 = sizes.front();
  std::string name1 = size1->getName();
  EXPECT_EQ(name1,u8"サイズ1");
  EXPECT_EQ(size1->getWidth(),90);
  EXPECT_EQ(size1->getHeight(),100);
  const rba::RBASize* size2 = sizes.back();
  EXPECT_EQ(size2->getName(),u8"サイズ2");
  EXPECT_EQ(size2->getWidth(),40);
  EXPECT_EQ(size2->getHeight(),50);
}

}

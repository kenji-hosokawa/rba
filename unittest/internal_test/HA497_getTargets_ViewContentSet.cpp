// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getTargets_ViewContentSet.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_getTargets_ViewContentSet.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

using namespace rba;

HA497_getTargets_ViewContentSet::HA497_getTargets_ViewContentSet(void)
{
}

HA497_getTargets_ViewContentSet::~HA497_getTargets_ViewContentSet(void)
{
}

void HA497_getTargets_ViewContentSet::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_getTargets_ViewContentSet::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_getTargets_ViewContentSet, Test_1) {
  rba::RBAModelImpl* model1 = dynamic_cast<RBAModelImpl*>((RBAModel*)arb->getModel());
  const std::list<const rba::RBAViewContentSet*> viewContentsets = model1->getViewContentSets();
  ASSERT_EQ(viewContentsets.size(), 1U);
  const rba::RBAViewContentSet* viewContentset = viewContentsets.front();
  const std::list<const rba::RBAViewContent*> viewContents = viewContentset->getTargets();
  ASSERT_EQ(viewContents.size(), 2U);
  const rba::RBAViewContent* viewContent1 = viewContents.front();
  std::string name1 = viewContent1->getName();
  EXPECT_EQ(name1,"A1");
  const rba::RBAViewContent* viewContent2 = viewContents.back();
  std::string name2 = viewContent2->getName();
  EXPECT_EQ(name2,"A2");
}

}

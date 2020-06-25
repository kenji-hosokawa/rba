// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA908_getTargets_SoundContentSet.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA908_getTargets_SoundContentSet.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

using namespace rba;

HA908_getTargets_SoundContentSet::HA908_getTargets_SoundContentSet(void)
{
}

HA908_getTargets_SoundContentSet::~HA908_getTargets_SoundContentSet(void)
{
}

void HA908_getTargets_SoundContentSet::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA908_getTargets_SoundContentSet::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA908_getTargets_SoundContentSet, Test_1) {
  rba::RBAModelImpl* model1 = dynamic_cast<RBAModelImpl*>(const_cast<RBAModel*>(arb->getModel()));
  const std::list<const rba::RBASoundContentSet*> soundContentsets = model1->getSoundContentSets();
  ASSERT_EQ(soundContentsets.size(), 1U);
  const rba::RBASoundContentSet* soundContentset = soundContentsets.front();
  const std::list<const rba::RBASoundContent*> soundContents = soundContentset->getTargets();
  ASSERT_EQ(soundContents.size(), 2U);
  const rba::RBASoundContent* soundContent1 = soundContents.front();
  std::string name1 = soundContent1->getName();
  EXPECT_EQ(name1,"A1");
  const rba::RBASoundContent* soundContent2 = soundContents.back();
  std::string name2 = soundContent2->getName();
  EXPECT_EQ(name2,"A2");
}

}

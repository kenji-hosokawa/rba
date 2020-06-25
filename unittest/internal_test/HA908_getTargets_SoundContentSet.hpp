// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA908_getTargets_SoundContentSet.hpp
 */

#ifndef HA908_GETTARGETS_SOUNDCONTENTSET_HPP
#define HA908_GETTARGETS_SOUNDCONTENTSET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA908_getTargets_SoundContentSet.json"

namespace {

class HA908_getTargets_SoundContentSet : public ::testing::Test {
protected:
  HA908_getTargets_SoundContentSet(void);
  virtual ~HA908_getTargets_SoundContentSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

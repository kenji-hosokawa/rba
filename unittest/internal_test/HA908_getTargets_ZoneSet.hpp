// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA908_getTargets_ZoneSet.hpp
 */

#ifndef HA908_GETTARGETS_ZONESET_HPP
#define HA908_GETTARGETS_ZONESET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA908_getTargets_ZoneSet.json"

namespace {

class HA908_getTargets_ZoneSet : public ::testing::Test {
protected:
  HA908_getTargets_ZoneSet(void);
  virtual ~HA908_getTargets_ZoneSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

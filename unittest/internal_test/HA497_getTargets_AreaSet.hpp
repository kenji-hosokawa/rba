// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getTargets_AreaSet.hpp
 */

#ifndef HA497_GETTARGETS_AREASET_HPP
#define HA497_GETTARGETS_AREASET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_getTargets_AreaSet.json"

namespace {

class HA497_getTargets_AreaSet : public ::testing::Test {
protected:
  HA497_getTargets_AreaSet(void);
  virtual ~HA497_getTargets_AreaSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

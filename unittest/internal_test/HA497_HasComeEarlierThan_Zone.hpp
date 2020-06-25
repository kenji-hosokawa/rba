// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_HasComeEarlierThan_Zone.hpp
 */

#ifndef HA497_HASCOMEEARLIERTHAN_ZONE_HPP
#define HA497_HASCOMEEARLIERTHAN_ZONE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_HasComeEarlierThan_Zone.json"

namespace {

class HA497_HasComeEarlierThan_Zone : public ::testing::Test {
protected:
  HA497_HasComeEarlierThan_Zone(void);
  virtual ~HA497_HasComeEarlierThan_Zone(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

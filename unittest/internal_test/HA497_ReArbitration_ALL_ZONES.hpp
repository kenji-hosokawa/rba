// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ReArbitration_ALL_ZONES.hpp
 */

#ifndef HA497_REARBITRATION_ALL_ZONES_HPP
#define HA497_REARBITRATION_ALL_ZONES_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ReArbitration_ALL_ZONES.json"

namespace {

class HA497_ReArbitration_ALL_ZONES : public ::testing::Test {
protected:
  HA497_ReArbitration_ALL_ZONES(void);
  virtual ~HA497_ReArbitration_ALL_ZONES(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

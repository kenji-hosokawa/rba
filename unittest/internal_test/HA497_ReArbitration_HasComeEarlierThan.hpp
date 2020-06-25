// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ReArbitration_HasComeEarlierThan.hpp
 */

#ifndef HA497_REARBITRATION_HASCOMEEARLIERTHAN_HPP
#define HA497_REARBITRATION_HASCOMEEARLIERTHAN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ReArbitration_HasComeEarlierThan.json"

namespace {

class HA497_ReArbitration_HasComeEarlierThan : public ::testing::Test {
protected:
  HA497_ReArbitration_HasComeEarlierThan(void);
  virtual ~HA497_ReArbitration_HasComeEarlierThan(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_FirstComeFirst.hpp
 */

#ifndef ARBITRATIONPOLICY_FIRSTCOMEFIRST_HPP
#define ARBITRATIONPOLICY_FIRSTCOMEFIRST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_FirstComeFirst.json"

namespace {

class ArbitrationPolicy_FirstComeFirst : public ::testing::Test {
protected:
  ArbitrationPolicy_FirstComeFirst(void);
  virtual ~ArbitrationPolicy_FirstComeFirst(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

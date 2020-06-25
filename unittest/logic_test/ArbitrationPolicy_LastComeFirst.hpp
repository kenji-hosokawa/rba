// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_LastComeFirst.hpp
 */

#ifndef ARBITRATIONPOLICY_LASTCOMEFIRST_HPP
#define ARBITRATIONPOLICY_LASTCOMEFIRST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_LastComeFirst.json"

namespace {

class ArbitrationPolicy_LastComeFirst : public ::testing::Test {
protected:
  ArbitrationPolicy_LastComeFirst(void);
  virtual ~ArbitrationPolicy_LastComeFirst(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

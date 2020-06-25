// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_PriorityFirstComeFirst.hpp
 */

#ifndef ARBITRATIONPOLICY_PRIORITYFIRSTCOMEFIRST_HPP
#define ARBITRATIONPOLICY_PRIORITYFIRSTCOMEFIRST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_PriorityFirstComeFirst.json"

namespace {

class ArbitrationPolicy_PriorityFirstComeFirst : public ::testing::Test {
protected:
  ArbitrationPolicy_PriorityFirstComeFirst(void);
  virtual ~ArbitrationPolicy_PriorityFirstComeFirst(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

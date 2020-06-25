// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_PriorityLastComeFirst.hpp
 */

#ifndef ARBITRATIONPOLICY_PRIORITYLASTCOMEFIRST_HPP
#define ARBITRATIONPOLICY_PRIORITYLASTCOMEFIRST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_PriorityLastComeFirst.json"

namespace {

class ArbitrationPolicy_PriorityLastComeFirst : public ::testing::Test {
protected:
  ArbitrationPolicy_PriorityLastComeFirst(void);
  virtual ~ArbitrationPolicy_PriorityLastComeFirst(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_PriorityLastComeFirst_Zone_.hpp
 */

#ifndef ARBITRATIONPOLICY_PRIORITYLASTCOMEFIRST_ZONE__HPP
#define ARBITRATIONPOLICY_PRIORITYLASTCOMEFIRST_ZONE__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_PriorityLastComeFirst_Zone_.json"

namespace {

class ArbitrationPolicy_PriorityLastComeFirst_Zone_ : public ::testing::Test {
protected:
  ArbitrationPolicy_PriorityLastComeFirst_Zone_(void);
  virtual ~ArbitrationPolicy_PriorityLastComeFirst_Zone_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

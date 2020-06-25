// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ArbitrationPolicy_FirstComeFirst_Zone_.hpp
 */

#ifndef ARBITRATIONPOLICY_FIRSTCOMEFIRST_ZONE__HPP
#define ARBITRATIONPOLICY_FIRSTCOMEFIRST_ZONE__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ArbitrationPolicy_FirstComeFirst_Zone_.json"

namespace {

class ArbitrationPolicy_FirstComeFirst_Zone_ : public ::testing::Test {
protected:
  ArbitrationPolicy_FirstComeFirst_Zone_(void);
  virtual ~ArbitrationPolicy_FirstComeFirst_Zone_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

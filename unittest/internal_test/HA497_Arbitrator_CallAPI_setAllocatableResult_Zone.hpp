// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Arbitrator_CallAPI_setAllocatableResult_Zone.hpp
 */

#ifndef HA497_ARBITRATOR_CALLAPI_SETALLOCATABLERESULT_ZONE_HPP
#define HA497_ARBITRATOR_CALLAPI_SETALLOCATABLERESULT_ZONE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_Arbitrator_CallAPI_setAllocatableResult_Zone.json"

namespace {

class HA497_Arbitrator_CallAPI_setAllocatableResult_Zone : public ::testing::Test {
protected:
  HA497_Arbitrator_CallAPI_setAllocatableResult_Zone(void);
  virtual ~HA497_Arbitrator_CallAPI_setAllocatableResult_Zone(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

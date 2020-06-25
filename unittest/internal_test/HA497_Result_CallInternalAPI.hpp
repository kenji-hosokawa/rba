// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Result_CallInternalAPI.hpp
 */

#ifndef HA497_RESULT_CALLINTERNALAPI_HPP
#define HA497_RESULT_CALLINTERNALAPI_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_Result_CallInternalAPI.json"

namespace {

class HA497_Result_CallInternalAPI : public ::testing::Test {
protected:
  HA497_Result_CallInternalAPI(void);
  virtual ~HA497_Result_CallInternalAPI(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

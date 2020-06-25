// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_StateValue_pre.hpp
 */

#ifndef HA497_STATEVALUE_PRE_HPP
#define HA497_STATEVALUE_PRE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_StateValue_pre.json"

namespace {

class HA497_StateValue_pre : public ::testing::Test {
protected:
  HA497_StateValue_pre(void);
  virtual ~HA497_StateValue_pre(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

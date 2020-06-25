// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * StateValue_origin.hpp
 */

#ifndef STATEVALUE_ORIGIN_HPP
#define STATEVALUE_ORIGIN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "StateValue_origin.json"

namespace {

class StateValue_origin : public ::testing::Test {
protected:
  StateValue_origin(void);
  virtual ~StateValue_origin(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

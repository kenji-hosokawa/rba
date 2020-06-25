// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * StateValue_skip.hpp
 */

#ifndef STATEVALUE_SKIP_HPP
#define STATEVALUE_SKIP_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "StateValue_skip.json"

namespace {

class StateValue_skip : public ::testing::Test {
protected:
  StateValue_skip(void);
  virtual ~StateValue_skip(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

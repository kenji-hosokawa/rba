// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * StateValue_Usecase.hpp
 */

#ifndef STATEVALUE_USECASE_HPP
#define STATEVALUE_USECASE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "StateValue_Usecase.json"

namespace {

class StateValue_Usecase : public ::testing::Test {
protected:
  StateValue_Usecase(void);
  virtual ~StateValue_Usecase(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

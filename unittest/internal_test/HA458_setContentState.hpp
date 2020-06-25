// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA458_setContentState.hpp
 */

#ifndef HA458_SETCONTENTSTATE_HPP
#define HA458_SETCONTENTSTATE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA458_setContentState.json"

namespace {

class HA458_setContentState : public ::testing::Test {
protected:
  HA458_setContentState(void);
  virtual ~HA458_setContentState(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

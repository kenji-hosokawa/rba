// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getSizes.hpp
 */

#ifndef HA497_GETSIZES_HPP
#define HA497_GETSIZES_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_getSizes.json"

namespace {

class HA497_getSizes : public ::testing::Test {
protected:
  HA497_getSizes(void);
  virtual ~HA497_getSizes(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

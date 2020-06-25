// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_AND_Area_MiddleToHigh_and_Low.hpp
 */

#ifndef IMPLIES_AND_AREA_MIDDLETOHIGH_AND_LOW_HPP
#define IMPLIES_AND_AREA_MIDDLETOHIGH_AND_LOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_AND_Area_MiddleToHigh_and_Low.json"

namespace {

class Implies_AND_Area_MiddleToHigh_and_Low : public ::testing::Test {
protected:
  Implies_AND_Area_MiddleToHigh_and_Low(void);
  virtual ~Implies_AND_Area_MiddleToHigh_and_Low(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

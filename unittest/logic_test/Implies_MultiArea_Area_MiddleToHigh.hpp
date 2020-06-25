// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_MultiArea_Area_MiddleToHigh.hpp
 */

#ifndef IMPLIES_MULTIAREA_AREA_MIDDLETOHIGH_HPP
#define IMPLIES_MULTIAREA_AREA_MIDDLETOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_MultiArea_Area_MiddleToHigh.json"

namespace {

class Implies_MultiArea_Area_MiddleToHigh : public ::testing::Test {
protected:
  Implies_MultiArea_Area_MiddleToHigh(void);
  virtual ~Implies_MultiArea_Area_MiddleToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

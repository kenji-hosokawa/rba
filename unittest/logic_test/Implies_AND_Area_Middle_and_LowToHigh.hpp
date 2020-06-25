// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_AND_Area_Middle_and_LowToHigh.hpp
 */

#ifndef IMPLIES_AND_AREA_MIDDLE_AND_LOWTOHIGH_HPP
#define IMPLIES_AND_AREA_MIDDLE_AND_LOWTOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_AND_Area_Middle_and_LowToHigh.json"

namespace {

class Implies_AND_Area_Middle_and_LowToHigh : public ::testing::Test {
protected:
  Implies_AND_Area_Middle_and_LowToHigh(void);
  virtual ~Implies_AND_Area_Middle_and_LowToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

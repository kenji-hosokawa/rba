// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_AND_Area_LowToHigh_and_Middle.hpp
 */

#ifndef IMPLIES_AND_AREA_LOWTOHIGH_AND_MIDDLE_HPP
#define IMPLIES_AND_AREA_LOWTOHIGH_AND_MIDDLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_AND_Area_LowToHigh_and_Middle.json"

namespace {

class Implies_AND_Area_LowToHigh_and_Middle : public ::testing::Test {
protected:
  Implies_AND_Area_LowToHigh_and_Middle(void);
  virtual ~Implies_AND_Area_LowToHigh_and_Middle(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

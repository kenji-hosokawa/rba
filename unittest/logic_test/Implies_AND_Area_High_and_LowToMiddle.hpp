// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_AND_Area_High_and_LowToMiddle.hpp
 */

#ifndef IMPLIES_AND_AREA_HIGH_AND_LOWTOMIDDLE_HPP
#define IMPLIES_AND_AREA_HIGH_AND_LOWTOMIDDLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_AND_Area_High_and_LowToMiddle.json"

namespace {

class Implies_AND_Area_High_and_LowToMiddle : public ::testing::Test {
protected:
  Implies_AND_Area_High_and_LowToMiddle(void);
  virtual ~Implies_AND_Area_High_and_LowToMiddle(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

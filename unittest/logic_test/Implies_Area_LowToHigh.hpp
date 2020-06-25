// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Area_LowToHigh.hpp
 */

#ifndef IMPLIES_AREA_LOWTOHIGH_HPP
#define IMPLIES_AREA_LOWTOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Area_LowToHigh.json"

namespace {

class Implies_Area_LowToHigh : public ::testing::Test {
protected:
  Implies_Area_LowToHigh(void);
  virtual ~Implies_Area_LowToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

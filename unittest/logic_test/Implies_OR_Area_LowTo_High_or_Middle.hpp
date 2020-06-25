// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_OR_Area_LowTo_High_or_Middle.hpp
 */

#ifndef IMPLIES_OR_AREA_LOWTO_HIGH_OR_MIDDLE_HPP
#define IMPLIES_OR_AREA_LOWTO_HIGH_OR_MIDDLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_OR_Area_LowTo_High_or_Middle.json"

namespace {

class Implies_OR_Area_LowTo_High_or_Middle : public ::testing::Test {
protected:
  Implies_OR_Area_LowTo_High_or_Middle(void);
  virtual ~Implies_OR_Area_LowTo_High_or_Middle(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

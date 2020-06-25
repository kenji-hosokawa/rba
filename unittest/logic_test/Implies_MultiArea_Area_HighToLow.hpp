// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_MultiArea_Area_HighToLow.hpp
 */

#ifndef IMPLIES_MULTIAREA_AREA_HIGHTOLOW_HPP
#define IMPLIES_MULTIAREA_AREA_HIGHTOLOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_MultiArea_Area_HighToLow.json"

namespace {

class Implies_MultiArea_Area_HighToLow : public ::testing::Test {
protected:
  Implies_MultiArea_Area_HighToLow(void);
  virtual ~Implies_MultiArea_Area_HighToLow(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

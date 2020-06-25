// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_MultiArea_Area_LowToMiddle.hpp
 */

#ifndef IMPLIES_MULTIAREA_AREA_LOWTOMIDDLE_HPP
#define IMPLIES_MULTIAREA_AREA_LOWTOMIDDLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_MultiArea_Area_LowToMiddle.json"

namespace {

class Implies_MultiArea_Area_LowToMiddle : public ::testing::Test {
protected:
  Implies_MultiArea_Area_LowToMiddle(void);
  virtual ~Implies_MultiArea_Area_LowToMiddle(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

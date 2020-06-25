// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Area_LowToHigh_Content_.hpp
 */

#ifndef IMPLIES_AREA_LOWTOHIGH_CONTENT__HPP
#define IMPLIES_AREA_LOWTOHIGH_CONTENT__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Area_LowToHigh_Content_.json"

namespace {

class Implies_Area_LowToHigh_Content_ : public ::testing::Test {
protected:
  Implies_Area_LowToHigh_Content_(void);
  virtual ~Implies_Area_LowToHigh_Content_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Cycle_Low_Area_ToHigh_Area_ToHigh_Content_ToLow_Content_.hpp
 */

#ifndef IMPLIES_CYCLE_LOW_AREA_TOHIGH_AREA_TOHIGH_CONTENT_TOLOW_CONTENT__HPP
#define IMPLIES_CYCLE_LOW_AREA_TOHIGH_AREA_TOHIGH_CONTENT_TOLOW_CONTENT__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Cycle_Low_Area_ToHigh_Area_ToHigh_Content_ToLow_Content_.json"

namespace {

class Implies_Cycle_Low_Area_ToHigh_Area_ToHigh_Content_ToLow_Content_ : public ::testing::Test {
protected:
  Implies_Cycle_Low_Area_ToHigh_Area_ToHigh_Content_ToLow_Content_(void);
  virtual ~Implies_Cycle_Low_Area_ToHigh_Area_ToHigh_Content_ToLow_Content_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

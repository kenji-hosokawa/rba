// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Cycle_High_Area_ToLow_Area_ToLow_Content_ToHigh_Content_.hpp
 */

#ifndef IMPLIES_CYCLE_HIGH_AREA_TOLOW_AREA_TOLOW_CONTENT_TOHIGH_CONTENT__HPP
#define IMPLIES_CYCLE_HIGH_AREA_TOLOW_AREA_TOLOW_CONTENT_TOHIGH_CONTENT__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Cycle_High_Area_ToLow_Area_ToLow_Content_ToHigh_Content_.json"

namespace {

class Implies_Cycle_High_Area_ToLow_Area_ToLow_Content_ToHigh_Content_ : public ::testing::Test {
protected:
  Implies_Cycle_High_Area_ToLow_Area_ToLow_Content_ToHigh_Content_(void);
  virtual ~Implies_Cycle_High_Area_ToLow_Area_ToLow_Content_ToHigh_Content_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

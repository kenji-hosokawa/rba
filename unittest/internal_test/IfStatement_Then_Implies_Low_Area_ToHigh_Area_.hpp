// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_Then_Implies_Low_Area_ToHigh_Area_.hpp
 */

#ifndef IFSTATEMENT_THEN_IMPLIES_LOW_AREA_TOHIGH_AREA__HPP
#define IFSTATEMENT_THEN_IMPLIES_LOW_AREA_TOHIGH_AREA__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_Then_Implies_Low_Area_ToHigh_Area_.json"

namespace {

class IfStatement_Then_Implies_Low_Area_ToHigh_Area_ : public ::testing::Test {
protected:
  IfStatement_Then_Implies_Low_Area_ToHigh_Area_(void);
  virtual ~IfStatement_Then_Implies_Low_Area_ToHigh_Area_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

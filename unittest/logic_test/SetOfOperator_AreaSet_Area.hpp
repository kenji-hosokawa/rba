// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_AreaSet_Area.hpp
 */

#ifndef SETOFOPERATOR_AREASET_AREA_HPP
#define SETOFOPERATOR_AREASET_AREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_AreaSet_Area.json"

namespace {

class SetOfOperator_AreaSet_Area : public ::testing::Test {
protected:
  SetOfOperator_AreaSet_Area(void);
  virtual ~SetOfOperator_AreaSet_Area(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

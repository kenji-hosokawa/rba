// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_AreaSet.hpp
 */

#ifndef SETOFOPERATOR_AREASET_HPP
#define SETOFOPERATOR_AREASET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_AreaSet.json"

namespace {

class SetOfOperator_AreaSet : public ::testing::Test {
protected:
  SetOfOperator_AreaSet(void);
  virtual ~SetOfOperator_AreaSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

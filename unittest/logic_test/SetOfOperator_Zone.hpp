// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_Zone.hpp
 */

#ifndef SETOFOPERATOR_ZONE_HPP
#define SETOFOPERATOR_ZONE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_Zone.json"

namespace {

class SetOfOperator_Zone : public ::testing::Test {
protected:
  SetOfOperator_Zone(void);
  virtual ~SetOfOperator_Zone(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

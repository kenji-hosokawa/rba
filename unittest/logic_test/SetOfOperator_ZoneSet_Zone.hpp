// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_ZoneSet_Zone.hpp
 */

#ifndef SETOFOPERATOR_ZONESET_ZONE_HPP
#define SETOFOPERATOR_ZONESET_ZONE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_ZoneSet_Zone.json"

namespace {

class SetOfOperator_ZoneSet_Zone : public ::testing::Test {
protected:
  SetOfOperator_ZoneSet_Zone(void);
  virtual ~SetOfOperator_ZoneSet_Zone(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

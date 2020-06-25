// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_ZoneSet.hpp
 */

#ifndef SETOFOPERATOR_ZONESET_HPP
#define SETOFOPERATOR_ZONESET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_ZoneSet.json"

namespace {

class SetOfOperator_ZoneSet : public ::testing::Test {
protected:
  SetOfOperator_ZoneSet(void);
  virtual ~SetOfOperator_ZoneSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_IfStatement_getReferenceObject_RhsBeforeArbitrate.hpp
 */

#ifndef HA497_IFSTATEMENT_GETREFERENCEOBJECT_RHSBEFOREARBITRATE_HPP
#define HA497_IFSTATEMENT_GETREFERENCEOBJECT_RHSBEFOREARBITRATE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_IfStatement_getReferenceObject_RhsBeforeArbitrate.json"

namespace {

class HA497_IfStatement_getReferenceObject_RhsBeforeArbitrate : public ::testing::Test {
protected:
  HA497_IfStatement_getReferenceObject_RhsBeforeArbitrate(void);
  virtual ~HA497_IfStatement_getReferenceObject_RhsBeforeArbitrate(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

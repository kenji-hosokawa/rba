// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_rearbitration_IsLowerThanEqualOperator.hpp
 */

#ifndef IFSTATEMENT_REARBITRATION_ISLOWERTHANEQUALOPERATOR_HPP
#define IFSTATEMENT_REARBITRATION_ISLOWERTHANEQUALOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_rearbitration_IsLowerThanEqualOperator.json"

namespace {

class IfStatement_rearbitration_IsLowerThanEqualOperator : public ::testing::Test {
protected:
  IfStatement_rearbitration_IsLowerThanEqualOperator(void);
  virtual ~IfStatement_rearbitration_IsLowerThanEqualOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

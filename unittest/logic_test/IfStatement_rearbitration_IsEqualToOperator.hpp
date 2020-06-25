// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_rearbitration_IsEqualToOperator.hpp
 */

#ifndef IFSTATEMENT_REARBITRATION_ISEQUALTOOPERATOR_HPP
#define IFSTATEMENT_REARBITRATION_ISEQUALTOOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_rearbitration_IsEqualToOperator.json"

namespace {

class IfStatement_rearbitration_IsEqualToOperator : public ::testing::Test {
protected:
  IfStatement_rearbitration_IsEqualToOperator(void);
  virtual ~IfStatement_rearbitration_IsEqualToOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

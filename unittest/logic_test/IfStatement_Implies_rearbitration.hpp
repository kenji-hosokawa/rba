// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_Implies_rearbitration.hpp
 */

#ifndef IFSTATEMENT_IMPLIES_REARBITRATION_HPP
#define IFSTATEMENT_IMPLIES_REARBITRATION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_Implies_rearbitration.json"

namespace {

class IfStatement_Implies_rearbitration : public ::testing::Test {
protected:
  IfStatement_Implies_rearbitration(void);
  virtual ~IfStatement_Implies_rearbitration(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

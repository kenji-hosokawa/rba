// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ImpliesOperator_IfStatement_Exists.hpp
 */

#ifndef IMPLIESOPERATOR_IFSTATEMENT_EXISTS_HPP
#define IMPLIESOPERATOR_IFSTATEMENT_EXISTS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ImpliesOperator_IfStatement_Exists.json"

namespace {

class ImpliesOperator_IfStatement_Exists : public ::testing::Test {
protected:
  ImpliesOperator_IfStatement_Exists(void);
  virtual ~ImpliesOperator_IfStatement_Exists(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

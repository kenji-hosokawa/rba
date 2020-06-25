// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ImpliesOperator_For_All_IfStatement.hpp
 */

#ifndef IMPLIESOPERATOR_FOR_ALL_IFSTATEMENT_HPP
#define IMPLIESOPERATOR_FOR_ALL_IFSTATEMENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ImpliesOperator_For_All_IfStatement.json"

namespace {

class ImpliesOperator_For_All_IfStatement : public ::testing::Test {
protected:
  ImpliesOperator_For_All_IfStatement(void);
  virtual ~ImpliesOperator_For_All_IfStatement(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

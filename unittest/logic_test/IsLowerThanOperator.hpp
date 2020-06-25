// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsLowerThanOperator.hpp
 */

#ifndef ISLOWERTHANOPERATOR_HPP
#define ISLOWERTHANOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsLowerThanOperator.json"

namespace {

class IsLowerThanOperator : public ::testing::Test {
protected:
  IsLowerThanOperator(void);
  virtual ~IsLowerThanOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

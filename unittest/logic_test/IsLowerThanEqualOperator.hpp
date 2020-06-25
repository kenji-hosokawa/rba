// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsLowerThanEqualOperator.hpp
 */

#ifndef ISLOWERTHANEQUALOPERATOR_HPP
#define ISLOWERTHANEQUALOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsLowerThanEqualOperator.json"

namespace {

class IsLowerThanEqualOperator : public ::testing::Test {
protected:
  IsLowerThanEqualOperator(void);
  virtual ~IsLowerThanEqualOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsGreaterThanEqualOperator.hpp
 */

#ifndef ISGREATERTHANEQUALOPERATOR_HPP
#define ISGREATERTHANEQUALOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsGreaterThanEqualOperator.json"

namespace {

class IsGreaterThanEqualOperator : public ::testing::Test {
protected:
  IsGreaterThanEqualOperator(void);
  virtual ~IsGreaterThanEqualOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

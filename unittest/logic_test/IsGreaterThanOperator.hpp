// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsGreaterThanOperator.hpp
 */

#ifndef ISGREATERTHANOPERATOR_HPP
#define ISGREATERTHANOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsGreaterThanOperator.json"

namespace {

class IsGreaterThanOperator : public ::testing::Test {
protected:
  IsGreaterThanOperator(void);
  virtual ~IsGreaterThanOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsEqualToOperator.hpp
 */

#ifndef ISEQUALTOOPERATOR_HPP
#define ISEQUALTOOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsEqualToOperator.json"

namespace {

class IsEqualToOperator : public ::testing::Test {
protected:
  IsEqualToOperator(void);
  virtual ~IsEqualToOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

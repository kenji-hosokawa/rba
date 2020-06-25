// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * OrOperator.hpp
 */

#ifndef OROPERATOR_HPP
#define OROPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "OrOperator.json"

namespace {

class OrOperator : public ::testing::Test {
protected:
  OrOperator(void);
  virtual ~OrOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

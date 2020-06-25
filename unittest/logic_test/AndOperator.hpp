// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AndOperator.hpp
 */

#ifndef ANDOPERATOR_HPP
#define ANDOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AndOperator.json"

namespace {

class AndOperator : public ::testing::Test {
protected:
  AndOperator(void);
  virtual ~AndOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

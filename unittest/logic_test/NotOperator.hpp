// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * NotOperator.hpp
 */

#ifndef NOTOPERATOR_HPP
#define NOTOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "NotOperator.json"

namespace {

class NotOperator : public ::testing::Test {
protected:
  NotOperator(void);
  virtual ~NotOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

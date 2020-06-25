// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ExistsOperator.hpp
 */

#ifndef EXISTSOPERATOR_HPP
#define EXISTSOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ExistsOperator.json"

namespace {

class ExistsOperator : public ::testing::Test {
protected:
  ExistsOperator(void);
  virtual ~ExistsOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ForAllOperator_include_ExistsOperator.hpp
 */

#ifndef FORALLOPERATOR_INCLUDE_EXISTSOPERATOR_HPP
#define FORALLOPERATOR_INCLUDE_EXISTSOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ForAllOperator_include_ExistsOperator.json"

namespace {

class ForAllOperator_include_ExistsOperator : public ::testing::Test {
protected:
  ForAllOperator_include_ExistsOperator(void);
  virtual ~ForAllOperator_include_ExistsOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

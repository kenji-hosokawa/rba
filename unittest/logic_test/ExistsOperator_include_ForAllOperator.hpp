// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ExistsOperator_include_ForAllOperator.hpp
 */

#ifndef EXISTSOPERATOR_INCLUDE_FORALLOPERATOR_HPP
#define EXISTSOPERATOR_INCLUDE_FORALLOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ExistsOperator_include_ForAllOperator.json"

namespace {

class ExistsOperator_include_ForAllOperator : public ::testing::Test {
protected:
  ExistsOperator_include_ForAllOperator(void);
  virtual ~ExistsOperator_include_ForAllOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

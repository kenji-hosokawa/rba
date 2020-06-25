// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ForAllOperator.hpp
 */

#ifndef FORALLOPERATOR_HPP
#define FORALLOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ForAllOperator.json"

namespace {

class ForAllOperator : public ::testing::Test {
protected:
  ForAllOperator(void);
  virtual ~ForAllOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

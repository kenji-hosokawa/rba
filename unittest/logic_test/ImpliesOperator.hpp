// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ImpliesOperator.hpp
 */

#ifndef IMPLIESOPERATOR_HPP
#define IMPLIESOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ImpliesOperator.json"

namespace {

class ImpliesOperator : public ::testing::Test {
protected:
  ImpliesOperator(void);
  virtual ~ImpliesOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

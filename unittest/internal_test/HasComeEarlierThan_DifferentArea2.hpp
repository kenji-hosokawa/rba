// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeEarlierThan_DifferentArea2.hpp
 */

#ifndef HASCOMEEARLIERTHAN_DIFFERENTAREA2_HPP
#define HASCOMEEARLIERTHAN_DIFFERENTAREA2_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeEarlierThan_DifferentArea2.json"

namespace {

class HasComeEarlierThan_DifferentArea2 : public ::testing::Test {
protected:
  HasComeEarlierThan_DifferentArea2(void);
  virtual ~HasComeEarlierThan_DifferentArea2(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

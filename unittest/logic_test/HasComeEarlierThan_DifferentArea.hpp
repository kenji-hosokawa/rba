// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeEarlierThan_DifferentArea.hpp
 */

#ifndef HASCOMEEARLIERTHAN_DIFFERENTAREA_HPP
#define HASCOMEEARLIERTHAN_DIFFERENTAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeEarlierThan_DifferentArea.json"

namespace {

class HasComeEarlierThan_DifferentArea : public ::testing::Test {
protected:
  HasComeEarlierThan_DifferentArea(void);
  virtual ~HasComeEarlierThan_DifferentArea(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

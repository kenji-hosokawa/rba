// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeEarlierThan_SameArea.hpp
 */

#ifndef HASCOMEEARLIERTHAN_SAMEAREA_HPP
#define HASCOMEEARLIERTHAN_SAMEAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeEarlierThan_SameArea.json"

namespace {

class HasComeEarlierThan_SameArea : public ::testing::Test {
protected:
  HasComeEarlierThan_SameArea(void);
  virtual ~HasComeEarlierThan_SameArea(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

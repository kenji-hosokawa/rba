// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeEarlierThan_Usecase.hpp
 */

#ifndef HASCOMEEARLIERTHAN_USECASE_HPP
#define HASCOMEEARLIERTHAN_USECASE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeEarlierThan_Usecase.json"

namespace {

class HasComeEarlierThan_Usecase : public ::testing::Test {
protected:
  HasComeEarlierThan_Usecase(void);
  virtual ~HasComeEarlierThan_Usecase(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

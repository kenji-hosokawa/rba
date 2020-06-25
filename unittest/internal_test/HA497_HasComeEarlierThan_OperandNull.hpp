// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_HasComeEarlierThan_OperandNull.hpp
 */

#ifndef HA497_HASCOMEEARLIERTHAN_OPERANDNULL_HPP
#define HA497_HASCOMEEARLIERTHAN_OPERANDNULL_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_HasComeEarlierThan_OperandNull.json"

namespace {

class HA497_HasComeEarlierThan_OperandNull : public ::testing::Test {
protected:
  HA497_HasComeEarlierThan_OperandNull(void);
  virtual ~HA497_HasComeEarlierThan_OperandNull(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

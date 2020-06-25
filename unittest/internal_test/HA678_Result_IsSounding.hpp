// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA678_Result_IsSounding.hpp
 */

#ifndef HA678_RESULT_ISVISIBLE_HPP
#define HA678_RESULT_ISVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA678_Result_IsSounding.json"

namespace {

class HA678_Result_IsSounding : public ::testing::Test {
protected:
  HA678_Result_IsSounding(void);
  virtual ~HA678_Result_IsSounding(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

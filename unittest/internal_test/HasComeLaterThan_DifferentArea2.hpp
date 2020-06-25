// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeLaterThan_DifferentArea2.hpp
 */

#ifndef HASCOMELATERTHAN_DIFFERENTAREA2_HPP
#define HASCOMELATERTHAN_DIFFERENTAREA2_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeLaterThan_DifferentArea2.json"

namespace {

class HasComeLaterThan_DifferentArea2 : public ::testing::Test {
protected:
  HasComeLaterThan_DifferentArea2(void);
  virtual ~HasComeLaterThan_DifferentArea2(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

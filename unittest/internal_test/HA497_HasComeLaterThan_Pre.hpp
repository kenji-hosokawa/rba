// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_HasComeLaterThan_Pre.hpp
 */

#ifndef HA497_HASCOMELATERTHAN_PRE_HPP
#define HA497_HASCOMELATERTHAN_PRE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_HasComeLaterThan_Pre.json"

namespace {

class HA497_HasComeLaterThan_Pre : public ::testing::Test {
protected:
  HA497_HasComeLaterThan_Pre(void);
  virtual ~HA497_HasComeLaterThan_Pre(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

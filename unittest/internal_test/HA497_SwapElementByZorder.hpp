// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_SwapElementByZorder.hpp
 */

#ifndef HA497_SWAPELEMENTBYZORDER_HPP
#define HA497_SWAPELEMENTBYZORDER_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_SwapElementByZorder.json"

namespace {

class HA497_SwapElementByZorder : public ::testing::Test {
protected:
  HA497_SwapElementByZorder(void);
  virtual ~HA497_SwapElementByZorder(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

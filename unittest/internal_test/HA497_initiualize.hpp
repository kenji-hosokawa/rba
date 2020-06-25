// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_initiualize.hpp
 */

#ifndef HA497_INITIUALIZE_HPP
#define HA497_INITIUALIZE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_initiualize.json"

namespace {

class HA497_initiualize : public ::testing::Test {
protected:
  HA497_initiualize(void);
  virtual ~HA497_initiualize(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

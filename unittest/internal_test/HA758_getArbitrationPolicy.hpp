// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA758_getArbitrationPolicy.hpp
 */

#ifndef HA758_GETARBITRATIONPOLICY
#define HA758_GETARBITRATIONPOLICY

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA758_getArbitrationPolicy.json"

namespace {

class HA758_getArbitrationPolicy : public ::testing::Test {
protected:
  HA758_getArbitrationPolicy(void);
  virtual ~HA758_getArbitrationPolicy(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA672_getprop.hpp
 */

#ifndef HA672_GETPROP_HPP
#define HA672_GETPROP_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA672_getprop.json"

namespace {

class HA672_getprop : public ::testing::Test {
protected:
  HA672_getprop(void);
  virtual ~HA672_getprop(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

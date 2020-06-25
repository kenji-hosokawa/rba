// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_ActiveContents.hpp
 */

#ifndef HA1209_ACTIVECONTENTS_HPP
#define HA1209_ACTIVECONTENTS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1209_ActiveContents.json"

namespace {

class HA1209_ActiveContents : public ::testing::Test {
protected:
  HA1209_ActiveContents();
  virtual ~HA1209_ActiveContents();

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_ = nullptr;
  rba::RBAArbitrator* arb_= nullptr;
  
};

}

#endif

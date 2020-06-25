// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA895_size.hpp
 */

#ifndef HA895_SIZE_HPP
#define HA895_SIZE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA895_size.json"

namespace {

using namespace rba;

class HA895_size : public ::testing::Test
{
protected:
  HA895_size();
  virtual ~HA895_size();
  virtual void SetUp();
  virtual void TearDown();
  rba::RBAModel* model_=nullptr;
};

}
#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1009_clear.hpp
 */

#ifndef HA1009_CLEAR_HPP
#define HA1009_CLEAR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1009_clear.json"

namespace {

class HA1009_clear : public ::testing::Test
{
protected:
  HA1009_clear();
  virtual ~HA1009_clear();

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<rba::RBAResult> result_;

};

}

#endif

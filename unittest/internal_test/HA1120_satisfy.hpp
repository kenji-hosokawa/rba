// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1120_satisfy.hpp
 */

#ifndef HA1120_SATISFY_HPP
#define HA1120_SATISFY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1120_satisfy.json"

namespace {

using namespace rba;

class HA1120_satisfy : public ::testing::Test
{
protected:
  HA1120_satisfy();
  virtual ~HA1120_satisfy();
  virtual void SetUp();
  virtual void TearDown();
  bool isSuccess(const std::string& msg);
  bool isSatisfiedConstraints(const std::string& msg);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;
};

}
#endif

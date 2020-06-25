// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA923_errorcheck.hpp
 */

#ifndef HA923_ERRORCHECK_HPP
#define HA923_ERRORCHECK_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA923_errorcheck.json"

namespace {

class HA923_errorcheck : public ::testing::Test
{
protected:
  HA923_errorcheck();
  virtual ~HA923_errorcheck();

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<rba::RBAResult> result_=nullptr;

};

}

#endif

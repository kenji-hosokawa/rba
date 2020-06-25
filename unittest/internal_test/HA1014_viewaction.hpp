// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1014_viewaction.hpp
 */

#ifndef HA1014_VIEWACTION_HPP
#define HA1014_VIEWACTION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1014_viewaction.json"

namespace {

using namespace rba;

class HA1014_viewaction : public ::testing::Test
{
protected:
  HA1014_viewaction();
  virtual ~HA1014_viewaction();
  virtual void SetUp();
  virtual void TearDown();
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;
};

}
#endif

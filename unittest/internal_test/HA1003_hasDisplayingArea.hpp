// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1003_hasDisplayingArea.hpp
 */

#ifndef HA1003_HASDISPLAYINGAREA_HPP
#define HA1003_HASDISPLAYINGAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1003_hasDisplayingArea.json"

namespace {

using namespace rba;

class HA1003_hasDisplayingArea : public ::testing::Test
{
protected:
  HA1003_hasDisplayingArea();
  virtual ~HA1003_hasDisplayingArea();
  virtual void SetUp();
  virtual void TearDown();
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;
};

}
#endif

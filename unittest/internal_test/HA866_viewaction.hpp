// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA866_viewaction.hpp
 */

#ifndef HA866_VIEWACTION_HPP
#define HA866_VIEWACTION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA866_viewaction.json"

namespace resultapi {

using namespace rba;

/**
 * APIテスト
 */
class HA866_viewaction : public ::testing::Test
{
protected:
  HA866_viewaction();
  virtual ~HA866_viewaction();
  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;

};

}
#endif

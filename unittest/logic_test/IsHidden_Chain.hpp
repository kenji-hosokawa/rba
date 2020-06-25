// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsHidden_Chain.hpp
 */

#ifndef ISHIDDEN_CHAIN_HPP
#define ISHIDDEN_CHAIN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsHidden_Chain.json"

namespace {

class IsHidden_Chain : public ::testing::Test {
protected:
  IsHidden_Chain(void);
  virtual ~IsHidden_Chain(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

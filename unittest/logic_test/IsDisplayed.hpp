// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsDisplayed.hpp
 */

#ifndef ISDISPLAYED_HPP
#define ISDISPLAYED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsDisplayed.json"

namespace {

class IsDisplayed : public ::testing::Test {
protected:
  IsDisplayed(void);
  virtual ~IsDisplayed(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

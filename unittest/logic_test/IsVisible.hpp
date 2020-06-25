// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsVisible.hpp
 */

#ifndef ISVISIBLE_HPP
#define ISVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsVisible.json"

namespace {

class IsVisible : public ::testing::Test {
protected:
  IsVisible(void);
  virtual ~IsVisible(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

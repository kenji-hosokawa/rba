// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Priority.hpp
 */

#ifndef PRIORITY_HPP
#define PRIORITY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Priority.json"

namespace {

class Priority : public ::testing::Test {
protected:
  Priority(void);
  virtual ~Priority(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

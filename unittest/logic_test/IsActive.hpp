// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsActive.hpp
 */

#ifndef ISACTIVE_HPP
#define ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsActive.json"

namespace {

class IsActive : public ::testing::Test {
protected:
  IsActive(void);
  virtual ~IsActive(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsHidden.hpp
 */

#ifndef ISHIDDEN_HPP
#define ISHIDDEN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsHidden.json"

namespace {

class IsHidden : public ::testing::Test {
protected:
  IsHidden(void);
  virtual ~IsHidden(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

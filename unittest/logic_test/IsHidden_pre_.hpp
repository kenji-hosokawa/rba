// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsHidden_pre_.hpp
 */

#ifndef ISHIDDEN_PRE__HPP
#define ISHIDDEN_PRE__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsHidden_pre_.json"

namespace {

class IsHidden_pre_ : public ::testing::Test {
protected:
  IsHidden_pre_(void);
  virtual ~IsHidden_pre_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

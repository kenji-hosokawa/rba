// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsHidden_contentValue.hpp
 */

#ifndef ISHIDDEN_CONTENTVALUE_HPP
#define ISHIDDEN_CONTENTVALUE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsHidden_contentValue.json"

namespace {

class IsHidden_contentValue : public ::testing::Test {
protected:
  IsHidden_contentValue(void);
  virtual ~IsHidden_contentValue(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

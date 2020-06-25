// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_ContentValue.hpp
 */

#ifndef PREVIOUSMODIFIER_CONTENTVALUE_HPP
#define PREVIOUSMODIFIER_CONTENTVALUE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_ContentValue.json"

namespace {

class PreviousModifier_ContentValue : public ::testing::Test {
protected:
  PreviousModifier_ContentValue(void);
  virtual ~PreviousModifier_ContentValue(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

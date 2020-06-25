// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsDisplayed.hpp
 */

#ifndef PREVIOUSMODIFIER_ISDISPLAYED_HPP
#define PREVIOUSMODIFIER_ISDISPLAYED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsDisplayed.json"

namespace {

class PreviousModifier_IsDisplayed : public ::testing::Test {
protected:
  PreviousModifier_IsDisplayed(void);
  virtual ~PreviousModifier_IsDisplayed(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

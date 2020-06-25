// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsVisible.hpp
 */

#ifndef PREVIOUSMODIFIER_ISVISIBLE_HPP
#define PREVIOUSMODIFIER_ISVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsVisible.json"

namespace {

class PreviousModifier_IsVisible : public ::testing::Test {
protected:
  PreviousModifier_IsVisible(void);
  virtual ~PreviousModifier_IsVisible(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

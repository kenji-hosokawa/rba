// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsActive_canceled.hpp
 */

#ifndef PREVIOUSMODIFIER_ISACTIVE_CANCELED_HPP
#define PREVIOUSMODIFIER_ISACTIVE_CANCELED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsActive_canceled.json"

namespace {

class PreviousModifier_IsActive_canceled : public ::testing::Test {
protected:
  PreviousModifier_IsActive_canceled(void);
  virtual ~PreviousModifier_IsActive_canceled(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsActive.hpp
 */

#ifndef PREVIOUSMODIFIER_ISACTIVE_HPP
#define PREVIOUSMODIFIER_ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsActive.json"

namespace {

class PreviousModifier_IsActive : public ::testing::Test {
protected:
  PreviousModifier_IsActive(void);
  virtual ~PreviousModifier_IsActive(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

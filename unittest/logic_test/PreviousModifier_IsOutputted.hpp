// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsOutputted.hpp
 */

#ifndef TESTPREVIOUSMODIFIER_ISDISPLAYED_HPP
#define TESTPREVIOUSMODIFIER_ISDISPLAYED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsOutputted.json"

namespace {

class PreviousModifier_IsOutputted : public ::testing::Test {
protected:
  PreviousModifier_IsOutputted(void);
  virtual ~PreviousModifier_IsOutputted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsAttenuated.hpp
 */

#ifndef PREVIOUSMODIFIER_ISATTENUATED_HPP
#define PREVIOUSMODIFIER_ISATTENUATED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsAttenuated.json"

namespace {

class PreviousModifier_IsAttenuated : public ::testing::Test {
protected:
  PreviousModifier_IsAttenuated(void);
  virtual ~PreviousModifier_IsAttenuated(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

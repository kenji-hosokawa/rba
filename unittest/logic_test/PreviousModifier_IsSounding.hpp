// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsSounding.hpp
 */

#ifndef PREVIOUSMODIFIER_ISSOUNDING_HPP
#define PREVIOUSMODIFIER_ISSOUNDING_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsSounding.json"

namespace {

class PreviousModifier_IsSounding : public ::testing::Test {
protected:
  PreviousModifier_IsSounding(void);
  virtual ~PreviousModifier_IsSounding(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

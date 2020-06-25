// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsMuted.hpp
 */

#ifndef PREVIOUSMODIFIER_ISMUTED_HPP
#define PREVIOUSMODIFIER_ISMUTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_IsMuted.json"

namespace {

class PreviousModifier_IsMuted : public ::testing::Test {
protected:
  PreviousModifier_IsMuted(void);
  virtual ~PreviousModifier_IsMuted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

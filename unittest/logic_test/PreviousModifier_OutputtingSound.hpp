// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_OutputtingSound.hpp
 */

#ifndef PREVIOUSMODIFIER_OUTPUTTINGSOUND_HPP
#define PREVIOUSMODIFIER_OUTPUTTINGSOUND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_OutputtingSound.json"

namespace {

class PreviousModifier_OutputtingSound : public ::testing::Test {
protected:
  PreviousModifier_OutputtingSound(void);
  virtual ~PreviousModifier_OutputtingSound(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

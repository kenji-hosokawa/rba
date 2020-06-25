// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_ContentValue_Sound_.hpp
 */

#ifndef PREVIOUSMODIFIER_CONTENTVALUE_SOUND__HPP
#define PREVIOUSMODIFIER_CONTENTVALUE_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_ContentValue_Sound_.json"

namespace {

class PreviousModifier_ContentValue_Sound_ : public ::testing::Test {
protected:
  PreviousModifier_ContentValue_Sound_(void);
  virtual ~PreviousModifier_ContentValue_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

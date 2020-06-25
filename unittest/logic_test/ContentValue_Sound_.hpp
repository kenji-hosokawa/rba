// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ContentValue_Sound_.hpp
 */

#ifndef CONTENTVALUE_SOUND__HPP
#define CONTENTVALUE_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ContentValue_Sound_.json"

namespace {

class ContentValue_Sound_ : public ::testing::Test {
protected:
  ContentValue_Sound_(void);
  virtual ~ContentValue_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

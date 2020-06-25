// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Priority_Sound_.hpp
 */

#ifndef PRIORITY_SOUND__HPP
#define PRIORITY_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Priority_Sound_.json"

namespace {

class Priority_Sound_ : public ::testing::Test {
protected:
  Priority_Sound_(void);
  virtual ~Priority_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

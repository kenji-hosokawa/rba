// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsActive_Sound_.hpp
 */

#ifndef ISACTIVE_SOUND__HPP
#define ISACTIVE_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsActive_Sound_.json"

namespace {

class IsActive_Sound_ : public ::testing::Test {
protected:
  IsActive_Sound_(void);
  virtual ~IsActive_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

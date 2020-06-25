// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetAllocatables_Sound_.hpp
 */

#ifndef GETALLOCATABLES_SOUND__HPP
#define GETALLOCATABLES_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetAllocatables_Sound_.json"

namespace {

class GetAllocatables_Sound_ : public ::testing::Test {
protected:
  GetAllocatables_Sound_(void);
  virtual ~GetAllocatables_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllocatedContent_Sound_.hpp
 */

#ifndef ALLOCATEDCONTENT_SOUND__HPP
#define ALLOCATEDCONTENT_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllocatedContent_Sound_.json"

namespace {

class AllocatedContent_Sound_ : public ::testing::Test {
protected:
  AllocatedContent_Sound_(void);
  virtual ~AllocatedContent_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

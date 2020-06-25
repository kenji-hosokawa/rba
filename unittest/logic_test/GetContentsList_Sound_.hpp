// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetContentsList_Sound_.hpp
 */

#ifndef GETCONTENTSLIST_SOUND__HPP
#define GETCONTENTSLIST_SOUND__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetContentsList_Sound_.json"

namespace {

class GetContentsList_Sound_ : public ::testing::Test {
protected:
  GetContentsList_Sound_(void);
  virtual ~GetContentsList_Sound_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

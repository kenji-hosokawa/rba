// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetAllocatables_Set.hpp
 */

#ifndef GETALLOCATABLES_SET_HPP
#define GETALLOCATABLES_SET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetAllocatables_Set.json"

namespace {

class GetAllocatables_Set : public ::testing::Test {
protected:
  GetAllocatables_Set(void);
  virtual ~GetAllocatables_Set(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

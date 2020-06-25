// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetAllocatables.hpp
 */

#ifndef GETALLOCATABLES_HPP
#define GETALLOCATABLES_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetAllocatables.json"

namespace {

class GetAllocatables : public ::testing::Test {
protected:
  GetAllocatables(void);
  virtual ~GetAllocatables(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

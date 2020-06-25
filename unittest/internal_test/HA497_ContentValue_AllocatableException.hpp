// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ContentValue_AllocatableException.hpp
 */

#ifndef HA497_CONTENTVALUE_ALLOCATABLEEXCEPTION_HPP
#define HA497_CONTENTVALUE_ALLOCATABLEEXCEPTION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ContentValue_AllocatableException.json"

namespace {

class HA497_ContentValue_AllocatableException : public ::testing::Test {
protected:
  HA497_ContentValue_AllocatableException(void);
  virtual ~HA497_ContentValue_AllocatableException(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

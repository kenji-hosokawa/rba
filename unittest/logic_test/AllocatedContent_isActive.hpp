// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllocatedContent_isActive.hpp
 */

#ifndef ALLOCATEDCONTENT_ISACTIVE_HPP
#define ALLOCATEDCONTENT_ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllocatedContent_isActive.json"

namespace {

class AllocatedContent_isActive : public ::testing::Test {
protected:
  AllocatedContent_isActive(void);
  virtual ~AllocatedContent_isActive(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

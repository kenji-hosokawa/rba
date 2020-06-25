// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllocatedContent_IsVisible.hpp
 */

#ifndef ALLOCATEDCONTENT_ISVISIBLE_HPP
#define ALLOCATEDCONTENT_ISVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllocatedContent_IsVisible.json"

namespace {

class AllocatedContent_IsVisible : public ::testing::Test {
protected:
  AllocatedContent_IsVisible(void);
  virtual ~AllocatedContent_IsVisible(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

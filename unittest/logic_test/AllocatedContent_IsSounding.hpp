// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllocatedContent_IsSounding.hpp
 */

#ifndef ALLOCATEDCONTENT_ISSOUNDING_HPP
#define ALLOCATEDCONTENT_ISSOUNDING_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllocatedContent_IsSounding.json"

namespace {

class AllocatedContent_IsSounding : public ::testing::Test {
protected:
  AllocatedContent_IsSounding(void);
  virtual ~AllocatedContent_IsSounding(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

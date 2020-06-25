// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllocatedContent.hpp
 */

#ifndef ALLOCATEDCONTENT_HPP
#define ALLOCATEDCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllocatedContent.json"

namespace {

class AllocatedContent : public ::testing::Test {
protected:
  AllocatedContent(void);
  virtual ~AllocatedContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

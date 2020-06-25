// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_AllocatedContent.hpp
 */

#ifndef PREVIOUSMODIFIER_ALLOCATEDCONTENT_HPP
#define PREVIOUSMODIFIER_ALLOCATEDCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_AllocatedContent.json"

namespace {

class PreviousModifier_AllocatedContent : public ::testing::Test {
protected:
  PreviousModifier_AllocatedContent(void);
  virtual ~PreviousModifier_AllocatedContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

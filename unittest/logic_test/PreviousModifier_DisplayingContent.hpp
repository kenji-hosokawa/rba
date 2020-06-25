// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_DisplayingContent.hpp
 */

#ifndef PREVIOUSMODIFIER_DISPLAYINGCONTENT_HPP
#define PREVIOUSMODIFIER_DISPLAYINGCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "PreviousModifier_DisplayingContent.json"

namespace {

class PreviousModifier_DisplayingContent : public ::testing::Test {
protected:
  PreviousModifier_DisplayingContent(void);
  virtual ~PreviousModifier_DisplayingContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * DisplayingContent_IsVisible.hpp
 */

#ifndef DISPLAYINGCONTENT_ISVISIBLE_HPP
#define DISPLAYINGCONTENT_ISVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "DisplayingContent_IsVisible.json"

namespace {

class DisplayingContent_IsVisible : public ::testing::Test {
protected:
  DisplayingContent_IsVisible(void);
  virtual ~DisplayingContent_IsVisible(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

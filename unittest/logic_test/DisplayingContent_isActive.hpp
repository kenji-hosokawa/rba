// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * DisplayingContent_isActive.hpp
 */

#ifndef DISPLAYINGCONTENT_ISACTIVE_HPP
#define DISPLAYINGCONTENT_ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "DisplayingContent_isActive.json"

namespace {

class DisplayingContent_isActive : public ::testing::Test {
protected:
  DisplayingContent_isActive(void);
  virtual ~DisplayingContent_isActive(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

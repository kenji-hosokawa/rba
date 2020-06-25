// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * DisplayingContent.hpp
 */

#ifndef DISPLAYINGCONTENT_HPP
#define DISPLAYINGCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "DisplayingContent.json"

namespace {

class DisplayingContent : public ::testing::Test {
protected:
  DisplayingContent(void);
  virtual ~DisplayingContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

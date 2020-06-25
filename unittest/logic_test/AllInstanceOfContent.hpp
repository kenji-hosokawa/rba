// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllInstanceOfContent.hpp
 */

#ifndef ALLINSTANCEOFCONTENT_HPP
#define ALLINSTANCEOFCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllInstanceOfContent.json"

namespace {

class AllInstanceOfContent : public ::testing::Test {
protected:
  AllInstanceOfContent(void);
  virtual ~AllInstanceOfContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

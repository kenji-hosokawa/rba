// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Content_HighToLow_Area_.hpp
 */

#ifndef IMPLIES_CONTENT_HIGHTOLOW_AREA__HPP
#define IMPLIES_CONTENT_HIGHTOLOW_AREA__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Content_HighToLow_Area_.json"

namespace {

class Implies_Content_HighToLow_Area_ : public ::testing::Test {
protected:
  Implies_Content_HighToLow_Area_(void);
  virtual ~Implies_Content_HighToLow_Area_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

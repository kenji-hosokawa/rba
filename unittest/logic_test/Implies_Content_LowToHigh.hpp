// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Content_LowToHigh.hpp
 */

#ifndef IMPLIES_CONTENT_LOWTOHIGH_HPP
#define IMPLIES_CONTENT_LOWTOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Content_LowToHigh.json"

namespace {

class Implies_Content_LowToHigh : public ::testing::Test {
protected:
  Implies_Content_LowToHigh(void);
  virtual ~Implies_Content_LowToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

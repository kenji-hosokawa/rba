// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Chain_Content_MiddleToLowToHigh.hpp
 */

#ifndef IMPLIES_CHAIN_CONTENT_MIDDLETOLOWTOHIGH_HPP
#define IMPLIES_CHAIN_CONTENT_MIDDLETOLOWTOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Chain_Content_MiddleToLowToHigh.json"

namespace {

class Implies_Chain_Content_MiddleToLowToHigh : public ::testing::Test {
protected:
  Implies_Chain_Content_MiddleToLowToHigh(void);
  virtual ~Implies_Chain_Content_MiddleToLowToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

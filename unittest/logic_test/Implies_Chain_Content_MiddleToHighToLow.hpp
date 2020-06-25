// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Chain_Content_MiddleToHighToLow.hpp
 */

#ifndef IMPLIES_CHAIN_CONTENT_MIDDLETOHIGHTOLOW_HPP
#define IMPLIES_CHAIN_CONTENT_MIDDLETOHIGHTOLOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Chain_Content_MiddleToHighToLow.json"

namespace {

class Implies_Chain_Content_MiddleToHighToLow : public ::testing::Test {
protected:
  Implies_Chain_Content_MiddleToHighToLow(void);
  virtual ~Implies_Chain_Content_MiddleToHighToLow(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

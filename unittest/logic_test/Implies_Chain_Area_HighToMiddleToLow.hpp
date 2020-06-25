// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Chain_Area_HighToMiddleToLow.hpp
 */

#ifndef IMPLIES_CHAIN_AREA_HIGHTOMIDDLETOLOW_HPP
#define IMPLIES_CHAIN_AREA_HIGHTOMIDDLETOLOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Chain_Area_HighToMiddleToLow.json"

namespace {

class Implies_Chain_Area_HighToMiddleToLow : public ::testing::Test {
protected:
  Implies_Chain_Area_HighToMiddleToLow(void);
  virtual ~Implies_Chain_Area_HighToMiddleToLow(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

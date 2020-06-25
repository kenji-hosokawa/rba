// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Chain_Low_Area_ToMiddle_Content_ToHigh_Content_.hpp
 */

#ifndef IMPLIES_CHAIN_LOW_AREA_TOMIDDLE_CONTENT_TOHIGH_CONTENT__HPP
#define IMPLIES_CHAIN_LOW_AREA_TOMIDDLE_CONTENT_TOHIGH_CONTENT__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Chain_Low_Area_ToMiddle_Content_ToHigh_Content_.json"

namespace {

class Implies_Chain_Low_Area_ToMiddle_Content_ToHigh_Content_ : public ::testing::Test {
protected:
  Implies_Chain_Low_Area_ToMiddle_Content_ToHigh_Content_(void);
  virtual ~Implies_Chain_Low_Area_ToMiddle_Content_ToHigh_Content_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

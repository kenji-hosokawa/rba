// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_Then_Implies_Low_Content_ToHigh_Content_.hpp
 */

#ifndef IFSTATEMENT_THEN_IMPLIES_LOW_CONTENT_TOHIGH_CONTENT__HPP
#define IFSTATEMENT_THEN_IMPLIES_LOW_CONTENT_TOHIGH_CONTENT__HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_Then_Implies_Low_Content_ToHigh_Content_.json"

namespace {

class IfStatement_Then_Implies_Low_Content_ToHigh_Content_ : public ::testing::Test {
protected:
  IfStatement_Then_Implies_Low_Content_ToHigh_Content_(void);
  virtual ~IfStatement_Then_Implies_Low_Content_ToHigh_Content_(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

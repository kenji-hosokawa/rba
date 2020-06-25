// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_Boolean.hpp
 */

#ifndef IFSTATEMENT_BOOLEAN_HPP
#define IFSTATEMENT_BOOLEAN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IfStatement_Boolean.json"

namespace {

class IfStatement_Boolean : public ::testing::Test {
protected:
  IfStatement_Boolean(void);
  virtual ~IfStatement_Boolean(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

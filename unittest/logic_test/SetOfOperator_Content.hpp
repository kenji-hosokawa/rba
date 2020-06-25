// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_Content.hpp
 */

#ifndef SETOFOPERATOR_CONTENT_HPP
#define SETOFOPERATOR_CONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_Content.json"

namespace {

class SetOfOperator_Content : public ::testing::Test {
protected:
  SetOfOperator_Content(void);
  virtual ~SetOfOperator_Content(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

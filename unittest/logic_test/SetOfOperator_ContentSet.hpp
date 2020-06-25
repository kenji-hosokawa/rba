// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_ContentSet.hpp
 */

#ifndef SETOFOPERATOR_CONTENTSET_HPP
#define SETOFOPERATOR_CONTENTSET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_ContentSet.json"

namespace {

class SetOfOperator_ContentSet : public ::testing::Test {
protected:
  SetOfOperator_ContentSet(void);
  virtual ~SetOfOperator_ContentSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

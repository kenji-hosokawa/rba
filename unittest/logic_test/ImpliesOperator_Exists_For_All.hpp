// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ImpliesOperator_Exists_For_All.hpp
 */

#ifndef IMPLIESOPERATOR_EXISTS_FOR_ALL_HPP
#define IMPLIESOPERATOR_EXISTS_FOR_ALL_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ImpliesOperator_Exists_For_All.json"

namespace {

class ImpliesOperator_Exists_For_All : public ::testing::Test {
protected:
  ImpliesOperator_Exists_For_All(void);
  virtual ~ImpliesOperator_Exists_For_All(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

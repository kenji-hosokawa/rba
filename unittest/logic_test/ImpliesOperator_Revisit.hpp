// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ImpliesOperator_Revisit.hpp
 */

#ifndef IMPLIESOPERATOR_REVISIT_HPP
#define IMPLIESOPERATOR_REVISIT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ImpliesOperator_Revisit.json"

namespace {

class ImpliesOperator_Revisit : public ::testing::Test {
protected:
  ImpliesOperator_Revisit(void);
  virtual ~ImpliesOperator_Revisit(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

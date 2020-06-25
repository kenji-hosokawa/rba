// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_cancelHidden_singleAllocatable_byAreaOperator.hpp
 */

#ifndef AFFECTEDAREA_CANCELHIDDEN_SINGLEALLOCATABLE_BYAREAOPERATOR_HPP
#define AFFECTEDAREA_CANCELHIDDEN_SINGLEALLOCATABLE_BYAREAOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_cancelHidden_singleAllocatable_byAreaOperator.json"

namespace {

class affectedArea_cancelHidden_singleAllocatable_byAreaOperator : public ::testing::Test {
protected:
  affectedArea_cancelHidden_singleAllocatable_byAreaOperator(void);
  virtual ~affectedArea_cancelHidden_singleAllocatable_byAreaOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

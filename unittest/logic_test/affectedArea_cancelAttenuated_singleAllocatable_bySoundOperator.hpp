// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_cancelAttenuated_singleAllocatable_bySoundOperator.hpp
 */

#ifndef AFFECTEDAREA_CANCELATTENUATED_SINGLEALLOCATABLE_BYSOUNDOPERATOR_HPP
#define AFFECTEDAREA_CANCELATTENUATED_SINGLEALLOCATABLE_BYSOUNDOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_cancelAttenuated_singleAllocatable_bySoundOperator.json"

namespace {

class affectedArea_cancelAttenuated_singleAllocatable_bySoundOperator : public ::testing::Test {
protected:
  affectedArea_cancelAttenuated_singleAllocatable_bySoundOperator(void);
  virtual ~affectedArea_cancelAttenuated_singleAllocatable_bySoundOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

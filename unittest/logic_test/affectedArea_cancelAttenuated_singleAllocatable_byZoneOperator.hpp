// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_cancelAttenuated_singleAllocatable_byZoneOperator.hpp
 */

#ifndef AFFECTEDAREA_CANCELATTENUATED_SINGLEALLOCATABLE_BYZONEOPERATOR_HPP
#define AFFECTEDAREA_CANCELATTENUATED_SINGLEALLOCATABLE_BYZONEOPERATOR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_cancelAttenuated_singleAllocatable_byZoneOperator.json"

namespace {

class affectedArea_cancelAttenuated_singleAllocatable_byZoneOperator : public ::testing::Test {
protected:
  affectedArea_cancelAttenuated_singleAllocatable_byZoneOperator(void);
  virtual ~affectedArea_cancelAttenuated_singleAllocatable_byZoneOperator(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_rollback_singleAllocatable.hpp
 */

#ifndef AFFECTEDAREA_ROLLBACK_SINGLEALLOCATABLE_HPP
#define AFFECTEDAREA_ROLLBACK_SINGLEALLOCATABLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_rollback_singleAllocatable.json"

namespace {

class affectedArea_rollback_singleAllocatable : public ::testing::Test {
protected:
  affectedArea_rollback_singleAllocatable(void);
  virtual ~affectedArea_rollback_singleAllocatable(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

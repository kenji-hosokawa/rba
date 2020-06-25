// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_reAllocate_singleAllocatable_chainConstraints.hpp
 */

#ifndef AFFECTEDAREA_REALLOCATE_SINGLEALLOCATABLE_CHAINCONSTRAINTS_HPP
#define AFFECTEDAREA_REALLOCATE_SINGLEALLOCATABLE_CHAINCONSTRAINTS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_reAllocate_singleAllocatable_chainConstraints.json"

namespace {

class affectedArea_reAllocate_singleAllocatable_chainConstraints : public ::testing::Test {
protected:
  affectedArea_reAllocate_singleAllocatable_chainConstraints(void);
  virtual ~affectedArea_reAllocate_singleAllocatable_chainConstraints(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_reAllocate_multiAllocatable_OR_OR.hpp
 */

#ifndef AFFECTEDAREA_REALLOCATE_MULTIALLOCATABLE_OR_OR_HPP
#define AFFECTEDAREA_REALLOCATE_MULTIALLOCATABLE_OR_OR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_reAllocate_multiAllocatable_OR_OR.json"

namespace {

class affectedArea_reAllocate_multiAllocatable_OR_OR : public ::testing::Test {
protected:
  affectedArea_reAllocate_multiAllocatable_OR_OR(void);
  virtual ~affectedArea_reAllocate_multiAllocatable_OR_OR(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

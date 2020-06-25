// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_reAllocate_multiAllocatable_AND_AND.hpp
 */

#ifndef AFFECTEDAREA_REALLOCATE_MULTIALLOCATABLE_AND_AND_HPP
#define AFFECTEDAREA_REALLOCATE_MULTIALLOCATABLE_AND_AND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_reAllocate_multiAllocatable_AND_AND.json"

namespace {

class affectedArea_reAllocate_multiAllocatable_AND_AND : public ::testing::Test {
protected:
  affectedArea_reAllocate_multiAllocatable_AND_AND(void);
  virtual ~affectedArea_reAllocate_multiAllocatable_AND_AND(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

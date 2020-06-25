// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_reAllocate_singleAllocatable_cycleConstraints_highArea_lowContent.hpp
 */

#ifndef AFFECTEDAREA_REALLOCATE_SINGLEALLOCATABLE_CYCLECONSTRAINTS_HIGHAREA_LOWCONTENT_HPP
#define AFFECTEDAREA_REALLOCATE_SINGLEALLOCATABLE_CYCLECONSTRAINTS_HIGHAREA_LOWCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_reAllocate_singleAllocatable_cycleConstraints_highArea_lowContent.json"

namespace {

class affectedArea_reAllocate_singleAllocatable_cycleConstraints_highArea_lowContent : public ::testing::Test {
protected:
  affectedArea_reAllocate_singleAllocatable_cycleConstraints_highArea_lowContent(void);
  virtual ~affectedArea_reAllocate_singleAllocatable_cycleConstraints_highArea_lowContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

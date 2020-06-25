// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * affectedArea_isAttenuated_multiAllocatable_cycleAffect.hpp
 */

#ifndef AFFECTEDAREA_ISATTENUATED_MULTIALLOCATABLE_CYCLEAFFECT_HPP
#define AFFECTEDAREA_ISATTENUATED_MULTIALLOCATABLE_CYCLEAFFECT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "affectedArea_isAttenuated_multiAllocatable_cycleAffect.json"

namespace {

class affectedArea_isAttenuated_multiAllocatable_cycleAffect : public ::testing::Test {
protected:
  affectedArea_isAttenuated_multiAllocatable_cycleAffect(void);
  virtual ~affectedArea_isAttenuated_multiAllocatable_cycleAffect(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

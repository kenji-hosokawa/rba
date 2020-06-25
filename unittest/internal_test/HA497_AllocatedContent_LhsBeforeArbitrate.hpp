// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_AllocatedContent_LhsBeforeArbitrate.hpp
 */

#ifndef HA497_ALLOCATEDCONTENT_LHSBEFOREARBITRATE_HPP
#define HA497_ALLOCATEDCONTENT_LHSBEFOREARBITRATE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_AllocatedContent_LhsBeforeArbitrate.json"

namespace {

class HA497_AllocatedContent_LhsBeforeArbitrate : public ::testing::Test {
protected:
  HA497_AllocatedContent_LhsBeforeArbitrate(void);
  virtual ~HA497_AllocatedContent_LhsBeforeArbitrate(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

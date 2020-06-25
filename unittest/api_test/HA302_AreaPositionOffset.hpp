// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA302_AreaPositionOffset.hpp
 */

#ifndef TESTAREPOSITIONOFFSET_HPP
#define TESTAREPOSITIONOFFSET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA302_AreaPositionOffset.json"

namespace {

class HA302_AreaPositionOffset : public ::testing::Test {
protected:
  HA302_AreaPositionOffset(void);
  virtual ~HA302_AreaPositionOffset(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

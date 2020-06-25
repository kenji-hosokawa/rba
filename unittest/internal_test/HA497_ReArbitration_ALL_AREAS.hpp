// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ReArbitration_ALL_AREAS.hpp
 */

#ifndef HA497_REARBITRATION_ALL_AREAS_HPP
#define HA497_REARBITRATION_ALL_AREAS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ReArbitration_ALL_AREAS.json"

namespace {

class HA497_ReArbitration_ALL_AREAS : public ::testing::Test {
protected:
  HA497_ReArbitration_ALL_AREAS(void);
  virtual ~HA497_ReArbitration_ALL_AREAS(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

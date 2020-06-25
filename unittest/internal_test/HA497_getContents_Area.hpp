// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_getContents_Area.hpp
 */

#ifndef HA497_GETCONTENTS_AREA_HPP
#define HA497_GETCONTENTS_AREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_getContents_Area.json"

namespace {

class HA497_getContents_Area : public ::testing::Test {
protected:
  HA497_getContents_Area(void);
  virtual ~HA497_getContents_Area(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ReArbitration_ContentsList.hpp
 */

#ifndef HA497_REARBITRATION_CONTENTSLIST_HPP
#define HA497_REARBITRATION_CONTENTSLIST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ReArbitration_ContentsList.json"

namespace {

class HA497_ReArbitration_ContentsList : public ::testing::Test {
protected:
  HA497_ReArbitration_ContentsList(void);
  virtual ~HA497_ReArbitration_ContentsList(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA562_ForAllOfImplicationRhs.hpp
 */

#ifndef HA562_FORALLOFIMPLICATIONRHS_HPP
#define HA562_FORALLOFIMPLICATIONRHS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA562_ForAllOfImplicationRhs.json"

namespace {

class HA562_ForAllOfImplicationRhs : public ::testing::Test {
protected:
  HA562_ForAllOfImplicationRhs(void);
  virtual ~HA562_ForAllOfImplicationRhs(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif
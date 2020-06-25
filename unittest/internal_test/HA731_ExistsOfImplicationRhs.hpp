// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA731_ExistsOfImplicationRhs.hpp
 */

#ifndef TESTFORALLOFIMPLICATIONRHS_HPP
#define TESTFORALLOFIMPLICATIONRHS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA731_ExistsOfImplicationRhs.json"

namespace {

class HA731_ExistsOfImplicationRhs : public ::testing::Test {
protected:
  HA731_ExistsOfImplicationRhs(void);
  virtual ~HA731_ExistsOfImplicationRhs(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

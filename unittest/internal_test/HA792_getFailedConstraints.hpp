// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA792_getFailedConstraints.hpp
 */

#ifndef HA792_GETFAILEDCONSTRAINTS_HPP
#define HA792_GETFAILEDCONSTRAINTS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA792_getFailedConstraints.json"

namespace {

class HA792_getFailedConstraints : public ::testing::Test
{
protected:
  HA792_getFailedConstraints();
  virtual ~HA792_getFailedConstraints();

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA457_CancelArbitration.hpp
 */

#ifndef HA457_CANCELARBITRATION_HPP
#define HA457_CANCELARBITRATION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA457_CancelArbitration.json"

namespace {

class HA457_CancelArbitration : public ::testing::Test {
protected:
  HA457_CancelArbitration(void);
  virtual ~HA457_CancelArbitration(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

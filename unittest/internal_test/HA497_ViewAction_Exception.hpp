// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ViewAction_Exception.hpp
 */

#ifndef HA497_ViewAction_Exception_HPP
#define HA497_ViewAction_Exception_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_ViewAction_Exception.json"

namespace {

class HA497_ViewAction_Exception : public ::testing::Test {
protected:
  HA497_ViewAction_Exception(void);
  virtual ~HA497_ViewAction_Exception(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

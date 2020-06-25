// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Rollback_exe_child.hpp
 */

#ifndef HA497_ROLLBACK_EXE_CHILD_HPP
#define HA497_ROLLBACK_EXE_CHILD_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_Rollback_exe_child.json"

namespace {

class HA497_Rollback_exe_child : public ::testing::Test {
protected:
  HA497_Rollback_exe_child(void);
  virtual ~HA497_Rollback_exe_child(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

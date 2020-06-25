// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_execute_list.hpp
 */

#ifndef HA497_EXECUTE_LIST_HPP
#define HA497_EXECUTE_LIST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_execute_list.json"

namespace {

class HA497_execute_list : public ::testing::Test {
protected:
  HA497_execute_list(void);
  virtual ~HA497_execute_list(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA578_If_Hidden.hpp
 */

#ifndef HA578_IF_HIDDEN_HPP
#define HA578_IF_HIDDEN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA578_If_Hidden.json"

namespace {

class HA578_If_Hidden : public ::testing::Test {
protected:
  HA578_If_Hidden(void);
  virtual ~HA578_If_Hidden(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

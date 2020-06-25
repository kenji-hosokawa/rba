// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsOutputted.hpp
 */

#ifndef ISOUTPUTTED_HPP
#define ISOUTPUTTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsOutputted.json"

namespace {

class IsOutputted : public ::testing::Test {
protected:
  IsOutputted(void);
  virtual ~IsOutputted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

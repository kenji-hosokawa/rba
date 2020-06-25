// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsAttenuated.hpp
 */

#ifndef ISATTENUATED_HPP
#define ISATTENUATED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsAttenuated.json"

namespace {

class IsAttenuated : public ::testing::Test {
protected:
  IsAttenuated(void);
  virtual ~IsAttenuated(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

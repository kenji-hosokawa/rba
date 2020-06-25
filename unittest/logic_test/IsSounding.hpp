// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsSounding.hpp
 */

#ifndef ISSOUNDING_HPP
#define ISSOUNDING_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsSounding.json"

namespace {

class IsSounding : public ::testing::Test {
protected:
  IsSounding(void);
  virtual ~IsSounding(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

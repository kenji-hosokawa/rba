// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllInstanceOfZone.hpp
 */

#ifndef ALLINSTANCEOFZONE_HPP
#define ALLINSTANCEOFZONE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllInstanceOfZone.json"

namespace {

class AllInstanceOfZone : public ::testing::Test {
protected:
  AllInstanceOfZone(void);
  virtual ~AllInstanceOfZone(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

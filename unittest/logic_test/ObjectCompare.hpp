// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ObjectCompare.hpp
 */

#ifndef OBJECTCOMPARE_HPP
#define OBJECTCOMPARE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "ObjectCompare.json"

namespace {

class ObjectCompare : public ::testing::Test {
protected:
  ObjectCompare(void);
  virtual ~ObjectCompare(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

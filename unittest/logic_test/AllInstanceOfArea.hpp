// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllInstanceOfArea.hpp
 */

#ifndef ALLINSTANCEOFAREA_HPP
#define ALLINSTANCEOFAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllInstanceOfArea.json"

namespace {

class AllInstanceOfArea : public ::testing::Test {
protected:
  AllInstanceOfArea(void);
  virtual ~AllInstanceOfArea(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

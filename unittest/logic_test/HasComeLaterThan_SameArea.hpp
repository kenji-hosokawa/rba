// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeLaterThan_SameArea.hpp
 */

#ifndef HASCOMELATERTHAN_SAMEAREA_HPP
#define HASCOMELATERTHAN_SAMEAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeLaterThan_SameArea.json"

namespace {

class HasComeLaterThan_SameArea : public ::testing::Test {
protected:
  HasComeLaterThan_SameArea(void);
  virtual ~HasComeLaterThan_SameArea(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

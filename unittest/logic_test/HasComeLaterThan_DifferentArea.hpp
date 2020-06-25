// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeLaterThan_DifferentArea.hpp
 */

#ifndef HASCOMELATERTHAN_DIFFERENTAREA_HPP
#define HASCOMELATERTHAN_DIFFERENTAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeLaterThan_DifferentArea.json"

namespace {

class HasComeLaterThan_DifferentArea : public ::testing::Test {
protected:
  HasComeLaterThan_DifferentArea(void);
  virtual ~HasComeLaterThan_DifferentArea(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

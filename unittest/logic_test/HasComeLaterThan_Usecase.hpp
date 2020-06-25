// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeLaterThan_Usecase.hpp
 */

#ifndef HASCOMELATERTHAN_USECASE_HPP
#define HASCOMELATERTHAN_USECASE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HasComeLaterThan_Usecase.json"

namespace {

class HasComeLaterThan_Usecase : public ::testing::Test {
protected:
  HasComeLaterThan_Usecase(void);
  virtual ~HasComeLaterThan_Usecase(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

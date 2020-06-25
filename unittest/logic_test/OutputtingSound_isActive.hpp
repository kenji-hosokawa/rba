// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * OutputtingSound_isActive.hpp
 */

#ifndef OUTPUTTINGSOUND_ISACTIVE_HPP
#define OUTPUTTINGSOUND_ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "OutputtingSound_isActive.json"

namespace {

class OutputtingSound_isActive : public ::testing::Test {
protected:
  OutputtingSound_isActive(void);
  virtual ~OutputtingSound_isActive(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * OutputtingSound_IsSounding.hpp
 */

#ifndef OUTPUTTINGSOUND_ISSOUNDING_HPP
#define OUTPUTTINGSOUND_ISSOUNDING_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "OutputtingSound_IsSounding.json"

namespace {

class OutputtingSound_IsSounding : public ::testing::Test {
protected:
  OutputtingSound_IsSounding(void);
  virtual ~OutputtingSound_IsSounding(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * OutputtingSound.hpp
 */

#ifndef OUTPUTTINGSOUND_HPP
#define OUTPUTTINGSOUND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "OutputtingSound.json"

namespace {

class OutputtingSound : public ::testing::Test {
protected:
  OutputtingSound(void);
  virtual ~OutputtingSound(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

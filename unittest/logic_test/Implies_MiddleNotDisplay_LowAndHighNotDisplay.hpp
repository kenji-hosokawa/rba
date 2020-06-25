// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_MiddleNotDisplay_LowAndHighNotDisplay.hpp
 */

#ifndef IMPLIES_MIDDLENOTDISPLAY_LOWANDHIGHNOTDISPLAY_HPP
#define IMPLIES_MIDDLENOTDISPLAY_LOWANDHIGHNOTDISPLAY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_MiddleNotDisplay_LowAndHighNotDisplay.json"

namespace {

class Implies_MiddleNotDisplay_LowAndHighNotDisplay : public ::testing::Test {
protected:
  Implies_MiddleNotDisplay_LowAndHighNotDisplay(void);
  virtual ~Implies_MiddleNotDisplay_LowAndHighNotDisplay(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

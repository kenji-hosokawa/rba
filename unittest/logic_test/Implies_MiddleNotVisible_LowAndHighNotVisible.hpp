// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_MiddleNotVisible_LowAndHighNotVisible.hpp
 */

#ifndef IMPLIES_MIDDLENOTVISIBLE_LOWANDHIGHNOTVISIBLE_HPP
#define IMPLIES_MIDDLENOTVISIBLE_LOWANDHIGHNOTVISIBLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_MiddleNotVisible_LowAndHighNotVisible.json"

namespace {

class Implies_MiddleNotVisible_LowAndHighNotVisible : public ::testing::Test {
protected:
  Implies_MiddleNotVisible_LowAndHighNotVisible(void);
  virtual ~Implies_MiddleNotVisible_LowAndHighNotVisible(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

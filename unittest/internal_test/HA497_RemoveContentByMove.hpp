// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_RemoveContentByMove.hpp
 */

#ifndef HA497_REMOVECONTENTBYMOVE_HPP
#define HA497_REMOVECONTENTBYMOVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_RemoveContentByMove.json"

namespace {

class HA497_RemoveContentByMove : public ::testing::Test {
protected:
  HA497_RemoveContentByMove(void);
  virtual ~HA497_RemoveContentByMove(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

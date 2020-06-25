// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_DisplayingContentImpl.hpp
 */

#ifndef HA497_DISPLAYINGCONTENTIMPL_HPP
#define HA497_DISPLAYINGCONTENTIMPL_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_DisplayingContentImpl.json"

namespace {

class HA497_DisplayingContentImpl : public ::testing::Test {
protected:
  HA497_DisplayingContentImpl(void);
  virtual ~HA497_DisplayingContentImpl(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

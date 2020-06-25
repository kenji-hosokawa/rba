// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetContentsList_Set.hpp
 */

#ifndef GETCONTENTSLIST_SET_HPP
#define GETCONTENTSLIST_SET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetContentsList_Set.json"

namespace {

class GetContentsList_Set : public ::testing::Test {
protected:
  GetContentsList_Set(void);
  virtual ~GetContentsList_Set(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

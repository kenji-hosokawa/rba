// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * GetContentsList.hpp
 */

#ifndef GETCONTENTSLIST_HPP
#define GETCONTENTSLIST_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "GetContentsList.json"

namespace {

class GetContentsList : public ::testing::Test {
protected:
  GetContentsList(void);
  virtual ~GetContentsList(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

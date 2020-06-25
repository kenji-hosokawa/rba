// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA492_AreaWithNoContents.hpp
 */

#ifndef HA492_AREAWITHNOCONTENTS_HPP
#define HA492_AREAWITHNOCONTENTS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA492_AreaWithNoContents.json"

namespace {

class HA492_AreaWithNoContents : public ::testing::Test {
protected:
  HA492_AreaWithNoContents(void);
  virtual ~HA492_AreaWithNoContents(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

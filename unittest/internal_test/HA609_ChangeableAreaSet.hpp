// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA609_ChangeableAreaSet.hpp
 */

#ifndef HA609_CHANGEABLEAREASET_HPP
#define HA609_CHANGEABLEAREASET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE "HA609_ChangeableAreaSet.json"

namespace {

class HA609_ChangeableAreaSet : public ::testing::Test {
protected:
  HA609_ChangeableAreaSet(void);
  virtual ~HA609_ChangeableAreaSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

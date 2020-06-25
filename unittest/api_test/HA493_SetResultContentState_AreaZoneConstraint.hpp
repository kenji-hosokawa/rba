// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetResultContentState_AreaZoneConstraint.hpp
 */

#ifndef HA493_SETRESULTCONTENTSTATE_AREAZONECONSTRAINT_HPP
#define HA493_SETRESULTCONTENTSTATE_AREAZONECONSTRAINT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA493_SetResultContentState_AreaZoneConstraint.json"

namespace {

class HA493_SetResultContentState_AreaZoneConstraint : public ::testing::Test {
protected:
  HA493_SetResultContentState_AreaZoneConstraint(void);
  virtual ~HA493_SetResultContentState_AreaZoneConstraint(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

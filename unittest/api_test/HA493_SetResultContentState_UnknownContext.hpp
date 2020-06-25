// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetResultContentState_UnknownContext.hpp
 */

#ifndef HA493_SETRESULTCONTENTSTATE_UNKNOWNCONTEXT_HPP
#define HA493_SETRESULTCONTENTSTATE_UNKNOWNCONTEXT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA493_SetResultContentState_UnknownContext.json"

namespace {

class HA493_SetResultContentState_UnknownContext : public ::testing::Test {
protected:
  HA493_SetResultContentState_UnknownContext(void);
  virtual ~HA493_SetResultContentState_UnknownContext(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

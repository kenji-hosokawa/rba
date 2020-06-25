// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA929_logmgr.hpp
 */

#ifndef HA929_LOGMGR_HPP
#define HA929_LOGMGR_HPP

#ifdef RBA_USE_LOG
#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA929_logmgr.json"

namespace {

class HA929_logmgr : public ::testing::Test
{
protected:
  HA929_logmgr();
  virtual ~HA929_logmgr();

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_=nullptr;

};

}
#endif

#endif

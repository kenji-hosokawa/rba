// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA929_logmgr.cpp
 */

#ifdef RBA_USE_LOG
#include <list>
#include <string>
#include "RBAJsonParser.hpp"
#include "RBALogManager.hpp"
#include "HA929_logmgr.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA929_logmgr::HA929_logmgr()
{
}

HA929_logmgr::~HA929_logmgr()
{
}

void HA929_logmgr::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
}

void HA929_logmgr::TearDown()
{
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
  rba::RBALogManager::setLogManager(nullptr);
}

TEST_F(HA929_logmgr, exec)
{
  RBALogManager* logManager = new RBALogManager();
  RBALogManager::setLogManager(logManager);
  EXPECT_NE(nullptr, RBALogManager::getLogManager());
  RBAArbitrator* arb = new RBAArbitrator(model_);
  ASSERT_NE(nullptr, arb);
  EXPECT_NE(nullptr, RBALogManager::getLogManager());
  EXPECT_EQ(logManager, RBALogManager::getLogManager());
  delete logManager;
  delete arb;
}

}
#endif

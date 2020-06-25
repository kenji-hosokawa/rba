// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Scene_CallAPI.hpp
 */

#ifndef HA497_SCENE_CALLAPI_HPP
#define HA497_SCENE_CALLAPI_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_Scene_CallAPI.json"

namespace {

class HA497_Scene_CallAPI : public ::testing::Test {
protected:
  HA497_Scene_CallAPI(void);
  virtual ~HA497_Scene_CallAPI(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

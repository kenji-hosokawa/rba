// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetSceneProperties.hpp
 */

#ifndef HA493_SETSCENEPROPERTIES_HPP
#define HA493_SETSCENEPROPERTIES_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA493_SetSceneProperties.json"

namespace {

class HA493_SetSceneProperties : public ::testing::Test {
protected:
  HA493_SetSceneProperties(void);
  virtual ~HA493_SetSceneProperties(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

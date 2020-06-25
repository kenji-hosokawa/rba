// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetSceneProperty.hpp
 */

#ifndef HA493_SETSCENEPROPERTY_HPP
#define HA493_SETSCENEPROPERTY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA493_SetSceneProperty.json"

namespace {

class HA493_SetSceneProperty : public ::testing::Test {
protected:
  HA493_SetSceneProperty(void);
  virtual ~HA493_SetSceneProperty(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA462_SimulationMode.hpp
 */

#ifndef TESTALLINSTANCEOFAREA_HPP
#define TESTALLINSTANCEOFAREA_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA462_SimulationMode.json"

namespace {

class HA462_SimulationMode : public ::testing::Test {
protected:
  HA462_SimulationMode(void);
  virtual ~HA462_SimulationMode(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA615_extmodel.hpp
 */

#ifndef HA615_EXTMODEL_HPP
#define HA615_EXTMODEL_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA615_extmodel.json"

namespace {

class HA615_extmodel : public ::testing::Test {
protected:
  HA615_extmodel();
  virtual ~HA615_extmodel();

  virtual void SetUp();
  virtual void TearDown();

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA605_isMuted.hpp
 */

#ifndef HA605_ISMUTED_HPP
#define HA605_ISMUTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA605_isMuted.json"

namespace {

class HA605_isMuted : public ::testing::Test {
protected:
  HA605_isMuted(void);
  virtual ~HA605_isMuted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

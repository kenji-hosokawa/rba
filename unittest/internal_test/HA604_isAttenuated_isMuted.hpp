// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA604_isAttenuated_isMuted.hpp
 */

#ifndef HA604_ISATTENUATED_ISMUTED_HPP
#define HA604_ISATTENUATED_ISMUTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA604_isAttenuated_isMuted.json"

namespace {

class HA604_isAttenuated_isMuted : public ::testing::Test {
protected:
  HA604_isAttenuated_isMuted(void);
  virtual ~HA604_isAttenuated_isMuted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

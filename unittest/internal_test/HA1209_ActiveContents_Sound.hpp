// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_ActiveContents_Sound.hpp
 */

#ifndef HA1209_ACTIVECONTENTS_SOUND_HPP
#define HA1209_ACTIVECONTENTS_SOUND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA1209_ActiveContents_Sound.json"

namespace {

class HA1209_ActiveContents_Sound : public ::testing::Test
{
protected:
  HA1209_ActiveContents_Sound()=default;
  virtual ~HA1209_ActiveContents_Sound()=default;

  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_ = nullptr;
  rba::RBAArbitrator* arb_= nullptr;
  
};

}

#endif

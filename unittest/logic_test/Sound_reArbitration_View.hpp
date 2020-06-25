// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Sound_reArbitration_View.hpp
 */

#ifndef SOUND_REARBITRATION_VIEW_HPP
#define SOUND_REARBITRATION_VIEW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Sound_reArbitration_View.json"

namespace {

class Sound_reArbitration_View : public ::testing::Test {
protected:
  Sound_reArbitration_View(void);
  virtual ~Sound_reArbitration_View(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

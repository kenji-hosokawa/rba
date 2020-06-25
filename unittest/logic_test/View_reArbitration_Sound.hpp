// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * View_reArbitration_Sound.hpp
 */

#ifndef VIEW_REARBITRATION_SOUND_HPP
#define VIEW_REARBITRATION_SOUND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "View_reArbitration_Sound.json"

namespace {

class View_reArbitration_Sound : public ::testing::Test {
protected:
  View_reArbitration_Sound(void);
  virtual ~View_reArbitration_Sound(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * synchronize_View_Sound.hpp
 */

#ifndef SYNCHRONIZE_VIEW_SOUND_HPP
#define SYNCHRONIZE_VIEW_SOUND_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "synchronize_View_Sound.json"

namespace {

class synchronize_View_Sound : public ::testing::Test {
protected:
  synchronize_View_Sound(void);
  virtual ~synchronize_View_Sound(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

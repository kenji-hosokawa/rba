// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * AllInstanceOfSoundContent.hpp
 */

#ifndef ALLINSTANCEOFSOUNDCONTENT_HPP
#define ALLINSTANCEOFSOUNDCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "AllInstanceOfSoundContent.json"

namespace {

class AllInstanceOfSoundContent : public ::testing::Test {
protected:
  AllInstanceOfSoundContent(void);
  virtual ~AllInstanceOfSoundContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_SoundContent.hpp
 */

#ifndef SETOFOPERATOR_SOUNDCONTENT_HPP
#define SETOFOPERATOR_SOUNDCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_SoundContent.json"

namespace {

class SetOfOperator_SoundContent : public ::testing::Test {
protected:
  SetOfOperator_SoundContent(void);
  virtual ~SetOfOperator_SoundContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

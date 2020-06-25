// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_SoundContentSet_SoundContent.hpp
 */

#ifndef SETOFOPERATOR_SOUNDCONTENTSET_SOUNDCONTENT_HPP
#define SETOFOPERATOR_SOUNDCONTENTSET_SOUNDCONTENT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_SoundContentSet_SoundContent.json"

namespace {

class SetOfOperator_SoundContentSet_SoundContent : public ::testing::Test {
protected:
  SetOfOperator_SoundContentSet_SoundContent(void);
  virtual ~SetOfOperator_SoundContentSet_SoundContent(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

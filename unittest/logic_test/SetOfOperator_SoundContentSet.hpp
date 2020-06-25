// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * SetOfOperator_SoundContentSet.hpp
 */

#ifndef SETOFOPERATOR_SOUNDCONTENTSET_HPP
#define SETOFOPERATOR_SOUNDCONTENTSET_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "SetOfOperator_SoundContentSet.json"

namespace {

class SetOfOperator_SoundContentSet : public ::testing::Test {
protected:
  SetOfOperator_SoundContentSet(void);
  virtual ~SetOfOperator_SoundContentSet(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

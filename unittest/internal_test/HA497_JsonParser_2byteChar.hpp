// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_JsonParser_2byteChar.hpp
 */

#ifndef HA497_JSONPARSER_2BYTECHAR_HPP
#define HA497_JSONPARSER_2BYTECHAR_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA497_JsonParser_2byteChar.json"

namespace {

class HA497_JsonParser_2byteChar : public ::testing::Test {
protected:
  HA497_JsonParser_2byteChar(void);
  virtual ~HA497_JsonParser_2byteChar(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

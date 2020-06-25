// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsMuted.hpp
 */

#ifndef ISMUTED_HPP
#define ISMUTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "IsMuted.json"

namespace {

class IsMuted : public ::testing::Test {
protected:
  IsMuted(void);
  virtual ~IsMuted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

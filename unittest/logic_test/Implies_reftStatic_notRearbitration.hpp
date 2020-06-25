// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_reftStatic_notRearbitration.hpp
 */

#ifndef IMPLIES_REFTSTATIC_NOTREARBITRATION_HPP
#define IMPLIES_REFTSTATIC_NOTREARBITRATION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_reftStatic_notRearbitration.json"

namespace {

class Implies_reftStatic_notRearbitration : public ::testing::Test {
protected:
  Implies_reftStatic_notRearbitration(void);
  virtual ~Implies_reftStatic_notRearbitration(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

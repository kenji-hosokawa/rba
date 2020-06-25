/**
 * Implies_OR_Area_High_or_LowToMiddle.hpp
 */

#ifndef IMPLIES_OR_AREA_HIGH_OR_LOWTOMIDDLE_HPP
#define IMPLIES_OR_AREA_HIGH_OR_LOWTOMIDDLE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_OR_Area_High_or_LowToMiddle.json"

namespace {

class Implies_OR_Area_High_or_LowToMiddle : public ::testing::Test {
protected:
  Implies_OR_Area_High_or_LowToMiddle(void);
  virtual ~Implies_OR_Area_High_or_LowToMiddle(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

/**
 * Implies_OR_Area_High_or_MiddleToLow.hpp
 */

#ifndef IMPLIES_OR_AREA_HIGH_OR_MIDDLETOLOW_HPP
#define IMPLIES_OR_AREA_HIGH_OR_MIDDLETOLOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_OR_Area_High_or_MiddleToLow.json"

namespace {

class Implies_OR_Area_High_or_MiddleToLow : public ::testing::Test {
protected:
  Implies_OR_Area_High_or_MiddleToLow(void);
  virtual ~Implies_OR_Area_High_or_MiddleToLow(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

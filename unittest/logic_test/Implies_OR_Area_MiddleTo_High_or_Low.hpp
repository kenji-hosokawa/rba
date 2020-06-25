/**
 * Implies_OR_Area_MiddleTo_High_or_Low.hpp
 */

#ifndef IMPLIES_OR_AREA_MIDDLETO_HIGH_OR_LOW_HPP
#define IMPLIES_OR_AREA_MIDDLETO_HIGH_OR_LOW_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_OR_Area_MiddleTo_High_or_Low.json"

namespace {

class Implies_OR_Area_MiddleTo_High_or_Low : public ::testing::Test {
protected:
  Implies_OR_Area_MiddleTo_High_or_Low(void);
  virtual ~Implies_OR_Area_MiddleTo_High_or_Low(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

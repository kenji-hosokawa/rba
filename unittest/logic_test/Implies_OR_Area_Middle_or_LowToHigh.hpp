/**
 * Implies_OR_Area_Middle_or_LowToHigh.hpp
 */

#ifndef IMPLIES_OR_AREA_MIDDLE_OR_LOWTOHIGH_HPP
#define IMPLIES_OR_AREA_MIDDLE_OR_LOWTOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_OR_Area_Middle_or_LowToHigh.json"

namespace {

class Implies_OR_Area_Middle_or_LowToHigh : public ::testing::Test {
protected:
  Implies_OR_Area_Middle_or_LowToHigh(void);
  virtual ~Implies_OR_Area_Middle_or_LowToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

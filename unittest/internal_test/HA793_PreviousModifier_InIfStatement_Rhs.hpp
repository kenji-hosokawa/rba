/**
 * HA793_PreviousModifier_InIfStatement_Rhs.hpp
 */

#ifndef HA793_PREVIOUSMODIFIER_INIFSTATEMENT_RHS_HPP
#define HA793_PREVIOUSMODIFIER_INIFSTATEMENT_RHS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA793_PreviousModifier_InIfStatement_Rhs.json"

namespace {

class HA793_PreviousModifier_InIfStatement_Rhs : public ::testing::Test {
protected:
  HA793_PreviousModifier_InIfStatement_Rhs(void);
  virtual ~HA793_PreviousModifier_InIfStatement_Rhs(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

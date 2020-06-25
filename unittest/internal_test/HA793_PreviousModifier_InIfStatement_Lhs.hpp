/**
 * HA793_PreviousModifier_InIfStatement_Lhs.hpp
 */

#ifndef HA793_PREVIOUSMODIFIER_INIFSTATEMENT_LHS_HPP
#define HA793_PREVIOUSMODIFIER_INIFSTATEMENT_LHS_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA793_PreviousModifier_InIfStatement_Lhs.json"

namespace {

class HA793_PreviousModifier_InIfStatement_Lhs : public ::testing::Test {
protected:
  HA793_PreviousModifier_InIfStatement_Lhs(void);
  virtual ~HA793_PreviousModifier_InIfStatement_Lhs(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

/**
 * HA919_Result_SatisfiesConstraints_GetSceneProperty.hpp
 */

#ifndef HA919_RESULT_SATISFIESCONSTRAINTS_GETSCENEPROPERTY_HPP
#define HA919_RESULT_SATISFIESCONSTRAINTS_GETSCENEPROPERTY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA919_Result_SatisfiesConstraints_GetSceneProperty.json"

namespace {

class HA919_Result_SatisfiesConstraints_GetSceneProperty : public ::testing::Test {
protected:
  HA919_Result_SatisfiesConstraints_GetSceneProperty(void);
  virtual ~HA919_Result_SatisfiesConstraints_GetSceneProperty(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

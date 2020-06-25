/**
 * HA760_ReArbitrateByIsAttenuated.hpp
 */

#ifndef HA760_REARBITRATEBYISATTENUATED_HPP
#define HA760_REARBITRATEBYISATTENUATED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA760_ReArbitrateByIsAttenuated.json"

namespace {

class HA760_ReArbitrateByIsAttenuated : public ::testing::Test {
protected:
  HA760_ReArbitrateByIsAttenuated(void);
  virtual ~HA760_ReArbitrateByIsAttenuated(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

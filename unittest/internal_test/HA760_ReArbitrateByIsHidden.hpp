/**
 * HA760_ReArbitrateByIsHidden.hpp
 */

#ifndef HA760_REARBITRATEBYISHIDDEN_HPP
#define HA760_REARBITRATEBYISHIDDEN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA760_ReArbitrateByIsHidden.json"

namespace {

class HA760_ReArbitrateByIsHidden : public ::testing::Test {
protected:
  HA760_ReArbitrateByIsHidden(void);
  virtual ~HA760_ReArbitrateByIsHidden(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

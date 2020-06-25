/**
 * HA760_ReArbitrateByIsMuted.hpp
 */

#ifndef HA760_REARBITRATEBYISMUTED_HPP
#define HA760_REARBITRATEBYISMUTED_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA760_ReArbitrateByIsMuted.json"

namespace {

class HA760_ReArbitrateByIsMuted : public ::testing::Test {
protected:
  HA760_ReArbitrateByIsMuted(void);
  virtual ~HA760_ReArbitrateByIsMuted(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

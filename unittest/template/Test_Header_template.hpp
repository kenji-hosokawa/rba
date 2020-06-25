/**
 * <FILENAME>
 */

#ifndef <GUARDNAME>
#define <GUARDNAME>

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "<TEST_SUITE_NAME>.json"

namespace {

class <TEST_SUITE_NAME> : public ::testing::Test {
protected:
  <TEST_SUITE_NAME>(void);
  virtual ~<TEST_SUITE_NAME>(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif

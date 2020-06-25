/**
 * HA721_parse.hpp
 */

#ifndef HA721_PARSE_HPP
#define HA721_PARSE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA721_parse.json" // HA459_evaluate.jsonと同じもの

namespace
{

class HA721_parse : public ::testing::Test
{
protected:
  HA721_parse();
  virtual ~HA721_parse();

  virtual void SetUp();
  virtual void TearDown();

};

}

#endif

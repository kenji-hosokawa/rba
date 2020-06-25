/**
 * <TEST_SUITE_NAME>.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "<HEADER_FILENAME>"
#include "TestCommon.hpp"

namespace {

using namespace rba;

<TEST_SUITE_NAME>::<TEST_SUITE_NAME>(void)
{
}

<TEST_SUITE_NAME>::~<TEST_SUITE_NAME>(void)
{
}

void <TEST_SUITE_NAME>::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void <TEST_SUITE_NAME>::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

<TEST_CASE_BODY>

}

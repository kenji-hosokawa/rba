/**
 * HA919_Result_SatisfiesConstraints_GetSceneProperty.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA919_Result_SatisfiesConstraints_GetSceneProperty.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA919_Result_SatisfiesConstraints_GetSceneProperty::HA919_Result_SatisfiesConstraints_GetSceneProperty(void)
{
}

HA919_Result_SatisfiesConstraints_GetSceneProperty::~HA919_Result_SatisfiesConstraints_GetSceneProperty(void)
{
}

void HA919_Result_SatisfiesConstraints_GetSceneProperty::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA919_Result_SatisfiesConstraints_GetSceneProperty::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA919_Result_SatisfiesConstraints_GetSceneProperty, satisfiesConstraints) {
  std::unique_ptr<RBAResult> result;
  result = arb->execute();
  EXPECT_TRUE(result->satisfiesConstraints());
  result = arb->execute();
  EXPECT_TRUE(result->satisfiesConstraints());
  result = arb->execute("C1");
  EXPECT_TRUE(result->satisfiesConstraints());
  result = arb->execute();
  EXPECT_TRUE(result->satisfiesConstraints());
  EXPECT_TRUE(result->satisfiesConstraints());
  result = arb->execute("A1");
  EXPECT_FALSE(result->satisfiesConstraints());
  EXPECT_FALSE(result->satisfiesConstraints());
  result = arb->execute();
  EXPECT_FALSE(result->satisfiesConstraints());
}
}

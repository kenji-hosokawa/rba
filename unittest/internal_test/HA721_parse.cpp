/**
 * HA721_parse.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA721_parse.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA721_parse::HA721_parse()
{
}

HA721_parse::~HA721_parse()
{
}

void HA721_parse::SetUp()
{
}

void HA721_parse::TearDown()
{
}

TEST_F(HA721_parse, parse)
{
  rba::RBAJsonParser parser;
  RBAModel* model1 = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model1);

  RBAArbitrator* arb = new RBAArbitrator(model1);

  RBAModel* model2 = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model2);

  EXPECT_NE(model1, model2);

  arb->setModel(model2);
  delete model1;
  model1 = nullptr;
  std::unique_ptr<rba::RBAResult> result = arb->execute(u8"コンテンツA1/NORMAL",
							true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  delete model2;
  delete arb;
}

}

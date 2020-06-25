// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_rearbitration.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "IfStatement_rearbitration.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

IfStatement_rearbitration::IfStatement_rearbitration(void)
{
}

IfStatement_rearbitration::~IfStatement_rearbitration(void)
{
}

void IfStatement_rearbitration::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void IfStatement_rearbitration::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(IfStatement_rearbitration, Test_rearbitrate) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"OFF",u8"コンテンツA1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"OFF",u8"コンテンツB1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"コンテンツC1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"OFF",u8"コンテンツA2",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"コンテンツB2",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"OFF",u8"コンテンツC2",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"コンテンツA3",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"OFF",u8"コンテンツB3",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"OFF",u8"コンテンツC3",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"エリアA",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    // check invisible
    EXPECT_FALSE(result->isVisible(area));
    if(result->isVisible(area) == true) {
      std::cerr << "AREA: " << area->getName() << std::endl;
    }
  }

  elems = {u8"Assert",u8"A",u8"エリアB",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    // check invisible
    EXPECT_FALSE(result->isVisible(area));
    if(result->isVisible(area) == true) {
      std::cerr << "AREA: " << area->getName() << std::endl;
    }
  }

  elems = {u8"Assert",u8"A",u8"エリアC",u8"コンテンツC1"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    // check visible
    EXPECT_TRUE(result->isVisible(area));
    if(result->isVisible(area) == false) {
      std::cerr << "AREA: " << area->getName() << std::endl;
    }
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_STREQ(expect.c_str(), content->getName().c_str());
  }


}

}

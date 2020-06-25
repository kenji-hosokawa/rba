// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IsActive_Sound_.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "IsActive_Sound_.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

IsActive_Sound_::IsActive_Sound_(void)
{
}

IsActive_Sound_::~IsActive_Sound_(void)
{
}

void IsActive_Sound_::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void IsActive_Sound_::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(IsActive_Sound_, Test_true) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"コンテンツA1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"ゾーンA",u8"コンテンツA1"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
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
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }


}
TEST_F(IsActive_Sound_, Test_false) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"コンテンツA2",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"ゾーンA",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}

}

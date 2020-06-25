// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * StateValue_Usecase.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "StateValue_Usecase.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

StateValue_Usecase::StateValue_Usecase(void)
{
}

StateValue_Usecase::~StateValue_Usecase(void)
{
}

void StateValue_Usecase::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void StateValue_Usecase::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(StateValue_Usecase, Test_2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"Winner",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"a1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"execute"};
  {
    //result = arb->execute("", true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"Assert",u8"A",u8"A",u8"Winner"};
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

  elems = {"Assert",u8"CANCEL",u8"a1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    if(state){
      ASSERT_NE(nullptr, state);
      // check active
      EXPECT_FALSE(result->isCancel(state));
    }else{
      const rba::RBASoundContentState* state = arb->getModel()->findSoundContentState(contextName);
      ASSERT_NE(nullptr, state);
      // check active
      EXPECT_FALSE(result->isCancel(state));
    }
  }


}
TEST_F(StateValue_Usecase, Test_1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"Winner",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"execute"};
  {
    //result = arb->execute("", true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"Assert",u8"A",u8"A",u8"Winner"};
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

}

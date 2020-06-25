// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * PreviousModifier_IsActive_canceled.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "PreviousModifier_IsActive_canceled.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

PreviousModifier_IsActive_canceled::PreviousModifier_IsActive_canceled(void)
{
}

PreviousModifier_IsActive_canceled::~PreviousModifier_IsActive_canceled(void)
{
}

void PreviousModifier_IsActive_canceled::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void PreviousModifier_IsActive_canceled::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(PreviousModifier_IsActive_canceled, Test_cancel_pre_active) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"A1",u8"NORMAL"};
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

  elems = {u8"Assert",u8"A",u8"A",u8"A1"};
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

  elems = {u8"Assert",u8"A",u8"B",u8"NULL"};
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

  elems = {u8"Assert",u8"A",u8"C",u8"NULL"};
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

  elems = {u8"Assert",u8"CANCEL",u8"A1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B2",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"C1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"C",u8"ON",u8"B2",u8"NORMAL"};
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

  elems = {u8"Assert",u8"A",u8"A",u8"NULL"};
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

  elems = {u8"Assert",u8"A",u8"B",u8"B2"};
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

  elems = {u8"Assert",u8"A",u8"C",u8"NULL"};
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

  elems = {u8"Assert",u8"CANCEL",u8"A1",u8"NORMAL",u8"true"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_TRUE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B2",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"C1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"C",u8"ON",u8"A1",u8"NORMAL"};
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

  elems = {u8"Assert",u8"A",u8"A",u8"A1"};
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

  elems = {u8"Assert",u8"A",u8"B",u8"NULL"};
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

  elems = {u8"Assert",u8"A",u8"C",u8"NULL"};
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

  elems = {u8"Assert",u8"CANCEL",u8"A1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B2",u8"NORMAL",u8"true"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_TRUE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"C1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"C",u8"ON",u8"B2",u8"NORMAL"};
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

  elems = {u8"Assert",u8"A",u8"A",u8"NULL"};
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

  elems = {u8"Assert",u8"A",u8"B",u8"B2"};
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

  elems = {u8"Assert",u8"A",u8"C",u8"NULL"};
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

  elems = {u8"Assert",u8"CANCEL",u8"A1",u8"NORMAL",u8"true"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_TRUE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"B2",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }

  elems = {u8"Assert",u8"CANCEL",u8"C1",u8"NORMAL",u8"false"};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    const rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    ASSERT_NE(nullptr, state);
    // check active
    EXPECT_FALSE(result->isCancel(state));
  }


}

}

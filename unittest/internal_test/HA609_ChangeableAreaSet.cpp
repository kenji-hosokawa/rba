// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA609_ChangeableAreaSet.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA609_ChangeableAreaSet.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA609_ChangeableAreaSet::HA609_ChangeableAreaSet(void)
{
}

HA609_ChangeableAreaSet::~HA609_ChangeableAreaSet(void)
{
}

void HA609_ChangeableAreaSet::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA609_ChangeableAreaSet::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA609_ChangeableAreaSet, Test_1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C","ON","A1","NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C","ON","B1","NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"Assert","A","A","NULL"};
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
  }

  elems = {"Assert","A","B","B1"};
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

  elems = {"Assert","A","C","NULL"};
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
  }


}
TEST_F(HA609_ChangeableAreaSet, Test_2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C","ON","A2","NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C","ON","B1","NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"Assert","A","A","NULL"};
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
  }

  elems = {"Assert","A","B","NULL"};
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
  }

  elems = {"Assert","A","C","NULL"};
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
  }


}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA493_SetResultContentState_UnknownContext.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA493_SetResultContentState_UnknownContext.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA493_SetResultContentState_UnknownContext::HA493_SetResultContentState_UnknownContext(void)
{
}

HA493_SetResultContentState_UnknownContext::~HA493_SetResultContentState_UnknownContext(void)
{
}

void HA493_SetResultContentState_UnknownContext::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA493_SetResultContentState_UnknownContext::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA493_SetResultContentState_UnknownContext, Test_UnknownContent) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  result = arb->setResultContentState("A", "X1/NORMAL");
  EXPECT_EQ(rba::RBAResultStatusType::UNKNOWN_CONTENT_STATE, result->getStatusType());

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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
      }
    }
  }


}
TEST_F(HA493_SetResultContentState_UnknownContext, Test_UnknownArea) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  result = arb->setResultContentState("X", "A1/NORMAL");
  EXPECT_EQ(rba::RBAResultStatusType::UNKNOWN_CONTENT_STATE, result->getStatusType());

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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
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
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
      }
    }
  }


}

}

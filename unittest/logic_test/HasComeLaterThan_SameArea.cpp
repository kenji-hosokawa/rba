// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HasComeLaterThan_SameArea.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HasComeLaterThan_SameArea.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HasComeLaterThan_SameArea::HasComeLaterThan_SameArea(void)
{
}

HasComeLaterThan_SameArea::~HasComeLaterThan_SameArea(void)
{
}

void HasComeLaterThan_SameArea::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HasComeLaterThan_SameArea::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HasComeLaterThan_SameArea, Test_TwoRequests1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"a1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"a2",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"a1"};
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
TEST_F(HasComeLaterThan_SameArea, Test_TwoRequests2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"a2",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"a1"};
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
TEST_F(HasComeLaterThan_SameArea, Test_TwoRequests3) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"a1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"a3",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"a3"};
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
TEST_F(HasComeLaterThan_SameArea, Test_OneRequest2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"a2",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"a2"};
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
TEST_F(HasComeLaterThan_SameArea, Test_OneRequest1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

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

  elems = {"Assert",u8"A",u8"A",u8"a1"};
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

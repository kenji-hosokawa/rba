/**
 * HA793_PreviousModifier_InIfStatement_Lhs.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA793_PreviousModifier_InIfStatement_Lhs.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA793_PreviousModifier_InIfStatement_Lhs::HA793_PreviousModifier_InIfStatement_Lhs(void)
{
}

HA793_PreviousModifier_InIfStatement_Lhs::~HA793_PreviousModifier_InIfStatement_Lhs(void)
{
}

void HA793_PreviousModifier_InIfStatement_Lhs::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA793_PreviousModifier_InIfStatement_Lhs::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA793_PreviousModifier_InIfStatement_Lhs, Test_1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"A1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"B1",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"A1"};
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

  elems = {"Assert",u8"A",u8"B",u8"NULL"};
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

  elems = {"Assert",u8"A",u8"C",u8"NULL"};
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
TEST_F(HA793_PreviousModifier_InIfStatement_Lhs, Test_4) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"C1",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"NULL"};
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

  elems = {"Assert",u8"A",u8"B",u8"NULL"};
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

  elems = {"Assert",u8"A",u8"C",u8"NULL"};
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
TEST_F(HA793_PreviousModifier_InIfStatement_Lhs, Test_3) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"A1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"C1",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"A1"};
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

  elems = {"Assert",u8"A",u8"B",u8"NULL"};
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

  elems = {"Assert",u8"A",u8"C",u8"C1"};
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
TEST_F(HA793_PreviousModifier_InIfStatement_Lhs, Test_2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {"C",u8"ON",u8"B1",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {"C",u8"ON",u8"A1",u8"NORMAL"};
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

  elems = {"Assert",u8"A",u8"A",u8"A1"};
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

  elems = {"Assert",u8"A",u8"B",u8"B1"};
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

  elems = {"Assert",u8"A",u8"C",u8"NULL"};
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

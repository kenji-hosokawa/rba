// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1014_viewaction.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1014_viewaction.hpp"

namespace {

using namespace rba;

HA1014_viewaction::HA1014_viewaction() {}
HA1014_viewaction::~HA1014_viewaction() {}

void HA1014_viewaction::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1014_viewaction::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

TEST_F(HA1014_viewaction, exec)
{
  // cont1表示
  result_ = arb_->execute(u8"cont1/NORMAL");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  // check ADD
  {
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(2u, viewActions.size());
    // ADD AreaA:cont1
    {
      const RBAViewAction* va = viewActions.front();
      EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
      const RBAArea* area = va->getArea();
      EXPECT_STREQ(u8"AreaA", area->getName().c_str());
      const RBAViewContent* cont = va->getContent();
      EXPECT_STREQ(u8"cont1", cont->getName().c_str());
    }
    // ADD AreaB:cont1
    {
      const RBAViewAction* va = viewActions.back();
      EXPECT_EQ(RBAViewActionType::TRANSITION_ADD, va->getViewActionType());
      const RBAArea* area = va->getArea();
      EXPECT_STREQ(u8"AreaB", area->getName().c_str());
      const RBAViewContent* cont = va->getContent();
      EXPECT_STREQ(u8"cont1", cont->getName().c_str());
    }
  }

  // cont2表示
  result_ = arb_->execute(u8"cont2/NORMAL");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  // check REPLACE
  {
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(1u, viewActions.size());
    // REPLACE AreaB:cont1->cont2
    {
      const RBAViewAction* va = viewActions.front();
      EXPECT_EQ(RBAViewActionType::TRANSITION_REPLACE, va->getViewActionType());
      const RBAArea* area = va->getArea();
      EXPECT_STREQ(u8"AreaB", area->getName().c_str());
      const RBAViewContent* contFrom = va->getFromContent();
      EXPECT_STREQ(u8"cont1", contFrom->getName().c_str());
      const RBAViewContent* contTo = va->getToContent();
      EXPECT_STREQ(u8"cont2", contTo->getName().c_str());
    }
  }
  
  // cont3表示
  result_ = arb_->execute(u8"cont3/NORMAL");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  {
    const std::list<const RBAViewAction*>
      viewActions = result_->getViewActions();
    ASSERT_EQ(3u, viewActions.size());
    bool checkAdd = false;
    bool checkRemove = false;
    bool checkMove = false;
    for(const RBAViewAction* va : viewActions) {
      switch(va->getViewActionType()) {
	case RBAViewActionType::TRANSITION_ADD:
	  {
	    // ADD AreaA:cont3
	    const RBAArea* area = va->getArea();
	    EXPECT_STREQ(u8"AreaA", area->getName().c_str());
	    const RBAViewContent* cont = va->getContent();
	    EXPECT_STREQ(u8"cont3", cont->getName().c_str());
	  }
	  checkAdd = true;
	  break;
	case RBAViewActionType::TRANSITION_REMOVE:
	  {
	    // REMOVE AreaB:cont2
	    const RBAArea* area = va->getArea();
	    EXPECT_STREQ(u8"AreaB", area->getName().c_str());
	    const RBAViewContent* cont = va->getContent();
	    EXPECT_STREQ(u8"cont2", cont->getName().c_str());
	  }
	  checkRemove = true;
	  break;
	case RBAViewActionType::MOVE:
	  {
	    // MOVE cont1 AreaA->AreaB
	    const RBAArea* areaFrom = va->getFromArea();
	    EXPECT_STREQ(u8"AreaA", areaFrom->getName().c_str());
	    const RBAArea* areaTo = va->getToArea();
	    EXPECT_STREQ(u8"AreaB", areaTo->getName().c_str());
	    const RBAViewContent* cont = va->getContent();
	    EXPECT_STREQ(u8"cont1", cont->getName().c_str());
	  }
	  checkMove = true;
	  break;
      default:
	break;
      }
    }
    EXPECT_TRUE(checkAdd);
    EXPECT_TRUE(checkRemove);
    EXPECT_TRUE(checkMove);
  }
}

}

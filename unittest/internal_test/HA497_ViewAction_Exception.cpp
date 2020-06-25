// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ViewAction_Exception.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_ViewAction_Exception.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_ViewAction_Exception::HA497_ViewAction_Exception(void)
{
}

HA497_ViewAction_Exception::~HA497_ViewAction_Exception(void)
{
}

void HA497_ViewAction_Exception::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_ViewAction_Exception::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_ViewAction_Exception, TRANSITION_ADD) {
  std::unique_ptr<RBAResult> result;
  result = arb->execute(u8"A1");
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  const std::list<const RBAViewAction*> vaList = result->getViewActions();
  ASSERT_EQ(vaList.size(),1U);
  for ( const rba::RBAViewAction* va : vaList ) {
    if (va->getViewActionType() == RBAViewActionType::TRANSITION_ADD) {
      EXPECT_EQ(va->getArea(),model->findArea(u8"A"));
      EXPECT_EQ(va->getFromContent(),nullptr);
      EXPECT_EQ(va->getToContent(),nullptr);
      EXPECT_EQ(va->getFromContentState(),nullptr);
      EXPECT_EQ(va->getToContentState(),nullptr);
      EXPECT_EQ(va->getFromArea(),nullptr);
      EXPECT_EQ(va->getToArea(),nullptr);
      EXPECT_EQ(va->getContent(),model->findViewContent(u8"A1"));
      EXPECT_EQ(va->getContentState(),model->findViewContentState(u8"A1/NORMAL"));
    } else {
      EXPECT_TRUE(false); // このパスは通り得ない。
    }
  }
}

TEST_F(HA497_ViewAction_Exception, TRANSITION_REMOVE) {
  std::unique_ptr<RBAResult> result;
  result = arb->execute(u8"A1");
  result = arb->execute(u8"A1",false);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  const std::list<const RBAViewAction*> vaList = result->getViewActions();
  ASSERT_EQ(vaList.size(),1U);
  for ( const rba::RBAViewAction* va : vaList ) {
    if (va->getViewActionType() == RBAViewActionType::TRANSITION_REMOVE) {
      EXPECT_EQ(va->getArea(),model->findArea(u8"A"));
      EXPECT_EQ(va->getFromContent(),nullptr);
      EXPECT_EQ(va->getToContent(),nullptr);
      EXPECT_EQ(va->getFromContentState(),nullptr);
      EXPECT_EQ(va->getToContentState(),nullptr);
      EXPECT_EQ(va->getFromArea(),nullptr);
      EXPECT_EQ(va->getToArea(),nullptr);
      EXPECT_EQ(va->getContent(),model->findViewContent(u8"A1"));
      EXPECT_EQ(va->getContentState(),model->findViewContentState(u8"A1/NORMAL"));
    } else {
      EXPECT_TRUE(false); // このパスは通り得ない。
    }
  }
}
TEST_F(HA497_ViewAction_Exception, TRANSITION_REPLACE) {
  std::unique_ptr<RBAResult> result;
  result = arb->execute(u8"A1");
  result = arb->execute(u8"A2");
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  const std::list<const RBAViewAction*> vaList = result->getViewActions();
  ASSERT_EQ(vaList.size(),1U);
  for ( const rba::RBAViewAction* va : vaList ) {
    if (va->getViewActionType() == RBAViewActionType::TRANSITION_REPLACE) {
      EXPECT_EQ(va->getArea(),model->findArea(u8"A"));
      EXPECT_EQ(va->getFromContent(),model->findViewContent(u8"A1"));
      EXPECT_EQ(va->getToContent(),model->findViewContent(u8"A2"));
      EXPECT_EQ(va->getFromContentState(),model->findViewContentState(u8"A1/NORMAL"));
      EXPECT_EQ(va->getToContentState(),model->findViewContentState(u8"A2/NORMAL"));
      EXPECT_EQ(va->getFromArea(),nullptr);
      EXPECT_EQ(va->getToArea(),nullptr);
      EXPECT_EQ(va->getContent(),nullptr);
      EXPECT_EQ(va->getContentState(),nullptr);
    } else {
      EXPECT_TRUE(false); // このパスは通り得ない。
    }
  }
}

TEST_F(HA497_ViewAction_Exception, MOVE) {
  std::unique_ptr<RBAResult> result;
  result = arb->execute(u8"B1");
  result = arb->execute(u8"B2");
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  const std::list<const RBAViewAction*> vaList = result->getViewActions();
  ASSERT_EQ(vaList.size(),2U);
  for ( const rba::RBAViewAction* va : vaList ) {
    if (va->getViewActionType() == RBAViewActionType::TRANSITION_ADD) {
      EXPECT_EQ(va->getArea(),model->findArea(u8"B"));
      EXPECT_EQ(va->getFromContent(),nullptr);
      EXPECT_EQ(va->getToContent(),nullptr);
      EXPECT_EQ(va->getFromContentState(),nullptr);
      EXPECT_EQ(va->getToContentState(),nullptr);
      EXPECT_EQ(va->getFromArea(),nullptr);
      EXPECT_EQ(va->getToArea(),nullptr);
      EXPECT_EQ(va->getContent(),model->findViewContent(u8"B2"));
      EXPECT_EQ(va->getContentState(),model->findViewContentState(u8"B2/NORMAL"));
    } else if (va->getViewActionType() == RBAViewActionType::MOVE){
      EXPECT_EQ(va->getArea(),nullptr);
      EXPECT_EQ(va->getFromContent(),nullptr);
      EXPECT_EQ(va->getToContent(),nullptr);
      EXPECT_EQ(va->getFromContentState(),nullptr);
      EXPECT_EQ(va->getToContentState(),nullptr);
      EXPECT_EQ(va->getFromArea(),model->findArea(u8"B"));
      EXPECT_EQ(va->getToArea(),model->findArea(u8"BB"));
      EXPECT_EQ(va->getContent(),model->findViewContent(u8"B1"));
      EXPECT_EQ(va->getContentState(),model->findViewContentState(u8"B1/NORMAL"));
    } else {
      EXPECT_TRUE(false); // このパスは通り得ない。
    }
  }
}
}

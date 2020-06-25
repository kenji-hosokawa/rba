// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_PositionContainer_CallAPI.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_PositionContainer_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_PositionContainer_CallAPI::HA497_PositionContainer_CallAPI(void)
{
}

HA497_PositionContainer_CallAPI::~HA497_PositionContainer_CallAPI(void)
{
}

void HA497_PositionContainer_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_PositionContainer_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_PositionContainer_CallAPI, getX) {
  const std::list<const RBAPositionContainer*> list_org
    = model->getPositionContainers();
  std::list<const RBAPositionContainer*> list;
  for(auto pos : list_org) {
    list.push_back(pos);
  }
  EXPECT_EQ(list.size(),9U);
  list.front();
  EXPECT_EQ(list.front()->getX(),0);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),-1000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),-3000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),5000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),7000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),9000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),11000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),13000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getX(),15000);
  list.pop_front();
}

TEST_F(HA497_PositionContainer_CallAPI, getY) {
  const std::list<const RBAPositionContainer*> list_org
    = model->getPositionContainers();
  std::list<const RBAPositionContainer*> list;
  for(auto pos : list_org) {
    list.push_back(pos);
  }
  EXPECT_EQ(list.size(),9U);
  list.front();
  EXPECT_EQ(list.front()->getY(),0);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),-2000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),-4000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),6000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),8000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),10000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),12000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),14000);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getY(),16000);
  list.pop_front();
}
TEST_F(HA497_PositionContainer_CallAPI, getBasePoint) {
  const std::list<const RBAPositionContainer*> list_org
    = model->getPositionContainers();
  std::list<const RBAPositionContainer*> list;
  for(auto pos : list_org) {
    list.push_back(pos);
  }
  EXPECT_EQ(list.size(),9U);
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::CENTER_BOTTOM);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::CENTER_MIDDLE);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::CENTER_TOP);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::LEFT_BOTTOM);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::LEFT_MIDDLE);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::LEFT_TOP);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::RIGHT_BOTTOM);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::RIGHT_MIDDLE);
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getBasePoint(),RBABasePoint::RIGHT_TOP);
  list.pop_front();
}
TEST_F(HA497_PositionContainer_CallAPI, getArea) {
  const std::list<const RBAPositionContainer*> list_org
    = model->getPositionContainers();
  std::list<const RBAPositionContainer*> list;
  for(auto pos : list_org) {
    list.push_back(pos);
  }
  EXPECT_EQ(list.size(),9U);
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"A"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"B"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"C"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"D"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"E"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"F"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"G"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"H"));
  list.pop_front();
  list.front();
  EXPECT_EQ(list.front()->getArea(),model->findArea(u8"I"));
  list.pop_front();
}
}

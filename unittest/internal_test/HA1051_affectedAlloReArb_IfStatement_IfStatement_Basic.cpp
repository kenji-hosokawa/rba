// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic.hpp"

namespace {

using namespace rba;

HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic() {}
HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::~HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic() {}

void HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::getAllocated(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  std::string contentName;
  if(area) {
    if(result_->isVisible(area)) {
      const RBAViewContentState* allocState = result_->getContentState(area);
      if(allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  }
  else {
    const RBAZone* zone = model_->findZone(allocName);
    if(result_->isSounding(zone)) {
      const RBASoundContentState* allocState = result_->getContentState(zone);
      if(allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  }
  return contentName;
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isCanceled(const std::string& msg,
                       const std::string& contentName)
{
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {
    // ビューの場合
    for(const RBAViewContentState* state : viewContent->getContentStates()) {
      if(result_->isCancel(state)) {
        return true;
      }
    }
  }
  else {
    // サウンドの場合
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    for(const RBASoundContentState* state : soundContent->getContentStates()) {
      if(result_->isCancel(state)) {
        return true;
      }
    }
  }

  return false;
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isEnableContext(const std::string& msg,
                            const std::string& contextName)
{
  // コンテントチェック
  std::string contentName
     = RBAViewContentState::getContentNameByContext(contextName);
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {
    std::string stateName
      = RBAViewContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {
      return true;
    }
    const RBAViewContentState* state = model_->findViewContentState(contextName);
    return state != nullptr;
  }
  else {
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    if(soundContent == nullptr) {
      return false;
    }
    std::string stateName
      = RBASoundContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {
      return true;
    }
    const RBASoundContentState* state = model_->findSoundContentState(contextName);
    return state != nullptr;
  }
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0004  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0005  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0006  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0007  C,on,E1,NORMAL,continue
  contexts.push_back(u8"E1/NORMAL");
  // 0008  C,on,F1,NORMAL,continue
  contexts.push_back(u8"F1/NORMAL");
  // 0009  C,on,G1,NORMAL,continue
  contexts.push_back(u8"G1/NORMAL");
  // 0010  C,on,P1,NORMAL
  contexts.push_back(u8"P1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=10"));
  EXPECT_TRUE(isSatisfiedConstraints("line=10"));
  // 0011  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"A"));
  // 0012  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=12", u8"B"));
  // 0013  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=13", u8"C"));
  // 0014  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=14", u8"D"));
  // 0015  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=15", u8"E"));
  // 0016  Assert,A,F,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"F"));
  // 0017  Assert,A,G,G1
  EXPECT_EQ(u8"G1",getAllocated("line=17", u8"G"));
  // 0018  Assert,A,P,P1
  EXPECT_EQ(u8"P1",getAllocated("line=18", u8"P"));
}

// 0020  #start 2
TEST_F(HA1051_affectedAlloReArb_IfStatement_IfStatement_Basic, Test_02)
{
  std::list<std::string> contexts;

  // 0021  CL
  arb_->clearArbitration();
  // 0022  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0023  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0024  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0025  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0026  C,on,E1,NORMAL,continue
  contexts.push_back(u8"E1/NORMAL");
  // 0027  C,on,F1,NORMAL,continue
  contexts.push_back(u8"F1/NORMAL");
  // 0028  C,on,G1,NORMAL,continue
  contexts.push_back(u8"G1/NORMAL");
  // 0029  C,on,Q1,NORMAL
  contexts.push_back(u8"Q1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=30", u8"A"));
  // 0031  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=31", u8"B"));
  // 0032  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=32", u8"C"));
  // 0033  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=33", u8"D"));
  // 0034  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=34", u8"E"));
  // 0035  Assert,A,F,F1
  EXPECT_EQ(u8"F1",getAllocated("line=35", u8"F"));
  // 0036  Assert,A,G,G1
  EXPECT_EQ(u8"G1",getAllocated("line=36", u8"G"));
  // 0037  Assert,A,Q,Q1
  EXPECT_EQ(u8"Q1",getAllocated("line=37", u8"Q"));
}

}

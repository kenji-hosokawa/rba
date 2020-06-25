// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1051_affectedAlloReArb_IfStatement_Implies_Basic.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1051_affectedAlloReArb_IfStatement_Implies_Basic.hpp"

namespace {

using namespace rba;

HA1051_affectedAlloReArb_IfStatement_Implies_Basic::HA1051_affectedAlloReArb_IfStatement_Implies_Basic() {}
HA1051_affectedAlloReArb_IfStatement_Implies_Basic::~HA1051_affectedAlloReArb_IfStatement_Implies_Basic() {}

void HA1051_affectedAlloReArb_IfStatement_Implies_Basic::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1051_affectedAlloReArb_IfStatement_Implies_Basic::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1051_affectedAlloReArb_IfStatement_Implies_Basic::getAllocated(const std::string& msg,
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

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isCanceled(const std::string& msg,
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

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1051_affectedAlloReArb_IfStatement_Implies_Basic::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isEnableContext(const std::string& msg,
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

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1051_affectedAlloReArb_IfStatement_Implies_Basic::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1051_affectedAlloReArb_IfStatement_Implies_Basic, Test_01)
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
  // 0008  C,on,P1,NORMAL
  contexts.push_back(u8"P1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=8"));
  EXPECT_TRUE(isSatisfiedConstraints("line=8"));
  // 0009  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=9", u8"A"));
  // 0010  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=10", u8"B"));
  // 0011  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=11", u8"C"));
  // 0012  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=12", u8"D"));
  // 0013  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"E"));
  // 0014  Assert,A,P,P1
  EXPECT_EQ(u8"P1",getAllocated("line=14", u8"P"));
}

// 0016  #start 2
TEST_F(HA1051_affectedAlloReArb_IfStatement_Implies_Basic, Test_02)
{
  std::list<std::string> contexts;

  // 0017  CL
  arb_->clearArbitration();
  // 0018  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0019  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0020  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0021  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0022  C,on,E1,NORMAL,continue
  contexts.push_back(u8"E1/NORMAL");
  // 0023  C,on,Q1,NORMAL
  contexts.push_back(u8"Q1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=23"));
  EXPECT_TRUE(isSatisfiedConstraints("line=23"));
  // 0024  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=24", u8"A"));
  // 0025  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"B"));
  // 0026  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=26", u8"C"));
  // 0027  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=27", u8"D"));
  // 0028  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=28", u8"E"));
  // 0029  Assert,A,Q,Q1
  EXPECT_EQ(u8"Q1",getAllocated("line=29", u8"Q"));
}

}

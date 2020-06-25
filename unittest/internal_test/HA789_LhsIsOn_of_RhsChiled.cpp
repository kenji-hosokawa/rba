// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA789_LhsIsOn_of_RhsChiled.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA789_LhsIsOn_of_RhsChiled.hpp"

namespace {

using namespace rba;

HA789_LhsIsOn_of_RhsChiled::HA789_LhsIsOn_of_RhsChiled() {}
HA789_LhsIsOn_of_RhsChiled::~HA789_LhsIsOn_of_RhsChiled() {}

void HA789_LhsIsOn_of_RhsChiled::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA789_LhsIsOn_of_RhsChiled::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA789_LhsIsOn_of_RhsChiled::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA789_LhsIsOn_of_RhsChiled::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA789_LhsIsOn_of_RhsChiled::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA789_LhsIsOn_of_RhsChiled::getAllocated(const std::string& msg,
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

bool HA789_LhsIsOn_of_RhsChiled::isCanceled(const std::string& msg,
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

bool HA789_LhsIsOn_of_RhsChiled::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA789_LhsIsOn_of_RhsChiled::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA789_LhsIsOn_of_RhsChiled::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA789_LhsIsOn_of_RhsChiled::isEnableContext(const std::string& msg,
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

bool HA789_LhsIsOn_of_RhsChiled::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA789_LhsIsOn_of_RhsChiled::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 OFFandOFF
TEST_F(HA789_LhsIsOn_of_RhsChiled, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=5", u8"A"));
  // 0006  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=6", u8"B"));
}

// 0008  #start 2 ONandOFF
TEST_F(HA789_LhsIsOn_of_RhsChiled, Test_02)
{
  std::list<std::string> contexts;

  // 0009  CL
  arb_->clearArbitration();
  // 0010  S,on,S1
  result_ = arb_->execute(u8"S1", true);
  EXPECT_TRUE(isSuccess("line=10"));
  // 0011  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=13", u8"A"));
  // 0014  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=14", u8"B"));
}

// 0016  #start 3 OFFandON
TEST_F(HA789_LhsIsOn_of_RhsChiled, Test_03)
{
  std::list<std::string> contexts;

  // 0017  CL
  arb_->clearArbitration();
  // 0018  S,on,S2
  result_ = arb_->execute(u8"S2", true);
  EXPECT_TRUE(isSuccess("line=18"));
  // 0019  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=21", u8"A"));
  // 0022  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=22", u8"B"));
}

// 0024  #start 4 ONandON
TEST_F(HA789_LhsIsOn_of_RhsChiled, Test_04)
{
  std::list<std::string> contexts;

  // 0025  CL
  arb_->clearArbitration();
  // 0026  S,on,S1
  result_ = arb_->execute(u8"S1", true);
  EXPECT_TRUE(isSuccess("line=26"));
  // 0027  S,on,S2
  result_ = arb_->execute(u8"S2", true);
  EXPECT_TRUE(isSuccess("line=27"));
  // 0028  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=28"));
  EXPECT_TRUE(isSatisfiedConstraints("line=28"));
  // 0029  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=30", u8"A"));
  // 0031  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=31", u8"B"));
}

}

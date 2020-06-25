// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_AllocatedContent_Mutedheck.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_AllocatedContent_Mutedheck.hpp"

namespace {

using namespace rba;

HA762_AllocatedContent_Mutedheck::HA762_AllocatedContent_Mutedheck() {}
HA762_AllocatedContent_Mutedheck::~HA762_AllocatedContent_Mutedheck() {}

void HA762_AllocatedContent_Mutedheck::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_AllocatedContent_Mutedheck::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_AllocatedContent_Mutedheck::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_AllocatedContent_Mutedheck::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_AllocatedContent_Mutedheck::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_AllocatedContent_Mutedheck::getAllocated(const std::string& msg,
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

bool HA762_AllocatedContent_Mutedheck::isCanceled(const std::string& msg,
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

bool HA762_AllocatedContent_Mutedheck::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_AllocatedContent_Mutedheck::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_AllocatedContent_Mutedheck::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_AllocatedContent_Mutedheck::isEnableContext(const std::string& msg,
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

bool HA762_AllocatedContent_Mutedheck::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_AllocatedContent_Mutedheck::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_AllocatedContent_Mutedheck, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=5", u8"A"));
  // 0006  Assert,A,B,b1,attenuated:false
  EXPECT_EQ(u8"b1",getAllocated("line=6", u8"B"));
  EXPECT_FALSE(isAttenuated("line=6", u8"B"));
  // 0007  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=7", u8"C"));
  // 0008  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=8", u8"a1"));
  // 0009  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=9", u8"a2"));
  // 0010  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=10", u8"b1"));
  // 0011  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=11", u8"b2"));
  // 0012  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=12", u8"c1"));
  // 0013  Assert,C,isCanceled,c2,false
  EXPECT_FALSE(isCanceled("line=13", u8"c2"));
}

// 0015  #start 2
TEST_F(HA762_AllocatedContent_Mutedheck, Test_02)
{
  std::list<std::string> contexts;

  // 0016  CL
  arb_->clearArbitration();
  // 0017  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=20", u8"A"));
  EXPECT_FALSE(isAttenuated("line=20", u8"A"));
  // 0021  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=21", u8"B"));
  // 0022  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=22", u8"C"));
  // 0023  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=23", u8"a1"));
  // 0024  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=24", u8"a2"));
  // 0025  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=25", u8"b1"));
  // 0026  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=26", u8"b2"));
  // 0027  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=27", u8"c1"));
  // 0028  Assert,C,isCanceled,c2,false
  EXPECT_FALSE(isCanceled("line=28", u8"c2"));
}

}

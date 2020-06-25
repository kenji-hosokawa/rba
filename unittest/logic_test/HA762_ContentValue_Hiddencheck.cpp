// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_ContentValue_Hiddencheck.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_ContentValue_Hiddencheck.hpp"

namespace {

using namespace rba;

HA762_ContentValue_Hiddencheck::HA762_ContentValue_Hiddencheck() {}
HA762_ContentValue_Hiddencheck::~HA762_ContentValue_Hiddencheck() {}

void HA762_ContentValue_Hiddencheck::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_ContentValue_Hiddencheck::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_ContentValue_Hiddencheck::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_ContentValue_Hiddencheck::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_ContentValue_Hiddencheck::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_ContentValue_Hiddencheck::getAllocated(const std::string& msg,
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

bool HA762_ContentValue_Hiddencheck::isCanceled(const std::string& msg,
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

bool HA762_ContentValue_Hiddencheck::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_ContentValue_Hiddencheck::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_ContentValue_Hiddencheck::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_ContentValue_Hiddencheck::isEnableContext(const std::string& msg,
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

bool HA762_ContentValue_Hiddencheck::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_ContentValue_Hiddencheck::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_ContentValue_Hiddencheck, Test_01)
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
  // 0005  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"A"));
  // 0006  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=6", u8"B"));
  // 0007  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"C"));
  // 0008  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=8", u8"a1"));
  // 0009  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=9", u8"b1"));
  // 0010  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=10", u8"c1"));
}

// 0012  #start 2
TEST_F(HA762_ContentValue_Hiddencheck, Test_02)
{
  std::list<std::string> contexts;

  // 0013  CL
  arb_->clearArbitration();
  // 0014  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=14"));
  EXPECT_TRUE(isSatisfiedConstraints("line=14"));
  // 0015  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=16"));
  EXPECT_TRUE(isSatisfiedConstraints("line=16"));
  // 0017  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=17", u8"A"));
  // 0018  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=18", u8"B"));
  // 0019  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=19", u8"C"));
  // 0020  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=20", u8"a1"));
  // 0021  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=21", u8"b1"));
  // 0022  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=22", u8"c1"));
}

}

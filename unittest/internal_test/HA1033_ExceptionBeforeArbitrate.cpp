// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1033_ExceptionBeforeArbitrate.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1033_ExceptionBeforeArbitrate.hpp"

namespace {

using namespace rba;

HA1033_ExceptionBeforeArbitrate::HA1033_ExceptionBeforeArbitrate() {}
HA1033_ExceptionBeforeArbitrate::~HA1033_ExceptionBeforeArbitrate() {}

void HA1033_ExceptionBeforeArbitrate::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1033_ExceptionBeforeArbitrate::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1033_ExceptionBeforeArbitrate::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1033_ExceptionBeforeArbitrate::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1033_ExceptionBeforeArbitrate::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1033_ExceptionBeforeArbitrate::getAllocated(const std::string& msg,
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

bool HA1033_ExceptionBeforeArbitrate::isCanceled(const std::string& msg,
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

bool HA1033_ExceptionBeforeArbitrate::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1033_ExceptionBeforeArbitrate::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1033_ExceptionBeforeArbitrate::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1033_ExceptionBeforeArbitrate::isEnableContext(const std::string& msg,
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

bool HA1033_ExceptionBeforeArbitrate::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1033_ExceptionBeforeArbitrate::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start HA1033_allocatedContent
TEST_F(HA1033_ExceptionBeforeArbitrate, HA1033_allocatedContent)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,Area_A,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"Area_A"));
  // 0005  Assert,A,Area_B,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"Area_B"));
  // 0007  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=7"));
  EXPECT_TRUE(isSatisfiedConstraints("line=7"));
  // 0008  Assert,A,Area_A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=8", u8"Area_A"));
  // 0009  Assert,A,Area_B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=9", u8"Area_B"));
}

// 0012  #start HA1033_displayingContent
TEST_F(HA1033_ExceptionBeforeArbitrate, HA1033_displayingContent)
{
  std::list<std::string> contexts;

  // 0013  CL
  arb_->clearArbitration();
  // 0014  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=14"));
  EXPECT_TRUE(isSatisfiedConstraints("line=14"));
  // 0015  Assert,A,Area_A,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"Area_A"));
  // 0016  Assert,A,Area_C,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"Area_C"));
  // 0018  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,Area_A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=19", u8"Area_A"));
  // 0020  Assert,A,Area_C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=20", u8"Area_C"));
}

// 0023  #start HA1033_outputtingSound
TEST_F(HA1033_ExceptionBeforeArbitrate, HA1033_outputtingSound)
{
  std::list<std::string> contexts;

  // 0024  CL
  arb_->clearArbitration();
  // 0025  C,on,y1,NORMAL
  result_ = arb_->execute(u8"y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=25"));
  EXPECT_TRUE(isSatisfiedConstraints("line=25"));
  // 0026  Assert,A,Zone_X,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=26", u8"Zone_X"));
  // 0027  Assert,A,Zone_Y,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=27", u8"Zone_Y"));
  // 0029  C,on,x1,NORMAL
  result_ = arb_->execute(u8"x1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  Assert,A,Zone_X,x1,attenuated:false
  EXPECT_EQ(u8"x1",getAllocated("line=30", u8"Zone_X"));
  EXPECT_FALSE(isAttenuated("line=30", u8"Zone_X"));
  // 0031  Assert,A,Zone_Y,y1,attenuated:false
  EXPECT_EQ(u8"y1",getAllocated("line=31", u8"Zone_Y"));
  EXPECT_FALSE(isAttenuated("line=31", u8"Zone_Y"));
}

}

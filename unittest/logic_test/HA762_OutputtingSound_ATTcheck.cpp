// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_OutputtingSound_ATTcheck.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_OutputtingSound_ATTcheck.hpp"

namespace {

using namespace rba;

HA762_OutputtingSound_ATTcheck::HA762_OutputtingSound_ATTcheck() {}
HA762_OutputtingSound_ATTcheck::~HA762_OutputtingSound_ATTcheck() {}

void HA762_OutputtingSound_ATTcheck::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_OutputtingSound_ATTcheck::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_OutputtingSound_ATTcheck::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_OutputtingSound_ATTcheck::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_OutputtingSound_ATTcheck::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_OutputtingSound_ATTcheck::getAllocated(const std::string& msg,
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

bool HA762_OutputtingSound_ATTcheck::isCanceled(const std::string& msg,
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

bool HA762_OutputtingSound_ATTcheck::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_OutputtingSound_ATTcheck::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_OutputtingSound_ATTcheck::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_OutputtingSound_ATTcheck::isEnableContext(const std::string& msg,
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

bool HA762_OutputtingSound_ATTcheck::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_OutputtingSound_ATTcheck::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_OutputtingSound_ATTcheck, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=4", u8"A"));
  // 0005  Assert,A,B,b1,attenuated:false
  EXPECT_EQ(u8"b1",getAllocated("line=5", u8"B"));
  EXPECT_FALSE(isAttenuated("line=5", u8"B"));
  // 0006  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=6", u8"C"));
  // 0007  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=7", u8"a1"));
  // 0008  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=8", u8"a2"));
  // 0009  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=9", u8"b1"));
  // 0010  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=10", u8"b2"));
  // 0011  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=11", u8"c1"));
  // 0012  Assert,C,isCanceled,c2,false
  EXPECT_FALSE(isCanceled("line=12", u8"c2"));
  // 0013  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=13"));
  EXPECT_TRUE(isSatisfiedConstraints("line=13"));
  // 0014  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=14", u8"A"));
  // 0015  Assert,A,B,b1,attenuated:false
  EXPECT_EQ(u8"b1",getAllocated("line=15", u8"B"));
  EXPECT_FALSE(isAttenuated("line=15", u8"B"));
  // 0016  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=16", u8"C"));
  // 0017  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=17", u8"a1"));
  // 0018  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=18", u8"a2"));
  // 0019  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=19", u8"b1"));
  // 0020  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=20", u8"b2"));
  // 0021  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=21", u8"c1"));
  // 0022  Assert,C,isCanceled,c2,false
  EXPECT_FALSE(isCanceled("line=22", u8"c2"));
  // 0023  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=23"));
  EXPECT_TRUE(isSatisfiedConstraints("line=23"));
  // 0024  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=24", u8"A"));
  EXPECT_FALSE(isAttenuated("line=24", u8"A"));
  // 0025  Assert,A,B,b1,attenuated:true
  EXPECT_EQ(u8"b1",getAllocated("line=25", u8"B"));
  EXPECT_TRUE(isAttenuated("line=25", u8"B"));
  // 0026  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=26", u8"C"));
  // 0027  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=27", u8"a1"));
  // 0028  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=28", u8"a2"));
  // 0029  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=29", u8"b1"));
  // 0030  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=30", u8"b2"));
  // 0031  Assert,C,isCanceled,c1,false
  EXPECT_FALSE(isCanceled("line=31", u8"c1"));
  // 0032  Assert,C,isCanceled,c2,false
  EXPECT_FALSE(isCanceled("line=32", u8"c2"));
}

}

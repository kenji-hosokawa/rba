// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_HasComeLaterThan_Usecase2_Sound.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_HasComeLaterThan_Usecase2_Sound.hpp"

namespace {

using namespace rba;

HA762_HasComeLaterThan_Usecase2_Sound::HA762_HasComeLaterThan_Usecase2_Sound() {}
HA762_HasComeLaterThan_Usecase2_Sound::~HA762_HasComeLaterThan_Usecase2_Sound() {}

void HA762_HasComeLaterThan_Usecase2_Sound::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_HasComeLaterThan_Usecase2_Sound::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_HasComeLaterThan_Usecase2_Sound::getAllocated(const std::string& msg,
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

bool HA762_HasComeLaterThan_Usecase2_Sound::isCanceled(const std::string& msg,
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

bool HA762_HasComeLaterThan_Usecase2_Sound::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_HasComeLaterThan_Usecase2_Sound::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isEnableContext(const std::string& msg,
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

bool HA762_HasComeLaterThan_Usecase2_Sound::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_HasComeLaterThan_Usecase2_Sound::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_HasComeLaterThan_Usecase2_Sound, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=4", u8"A"));
  EXPECT_FALSE(isAttenuated("line=4", u8"A"));
  // 0005  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=5", u8"B"));
}

// 0007  #start 2
TEST_F(HA762_HasComeLaterThan_Usecase2_Sound, Test_02)
{
  std::list<std::string> contexts;

  // 0008  CL
  arb_->clearArbitration();
  // 0009  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=9"));
  EXPECT_TRUE(isSatisfiedConstraints("line=9"));
  // 0010  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=10", u8"A"));
  // 0011  Assert,A,B,b1,attenuated:false
  EXPECT_EQ(u8"b1",getAllocated("line=11", u8"B"));
  EXPECT_FALSE(isAttenuated("line=11", u8"B"));
}

// 0013  #start 3
TEST_F(HA762_HasComeLaterThan_Usecase2_Sound, Test_03)
{
  std::list<std::string> contexts;

  // 0014  CL
  arb_->clearArbitration();
  // 0015  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=16"));
  EXPECT_TRUE(isSatisfiedConstraints("line=16"));
  // 0017  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=17", u8"A"));
  EXPECT_FALSE(isAttenuated("line=17", u8"A"));
  // 0018  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=18", u8"B"));
}

// 0020  #start 4
TEST_F(HA762_HasComeLaterThan_Usecase2_Sound, Test_04)
{
  std::list<std::string> contexts;

  // 0021  CL
  arb_->clearArbitration();
  // 0022  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=22"));
  EXPECT_TRUE(isSatisfiedConstraints("line=22"));
  // 0023  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=23"));
  EXPECT_TRUE(isSatisfiedConstraints("line=23"));
  // 0024  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=24", u8"A"));
  // 0025  Assert,A,B,b1,attenuated:false
  EXPECT_EQ(u8"b1",getAllocated("line=25", u8"B"));
  EXPECT_FALSE(isAttenuated("line=25", u8"B"));
}

}

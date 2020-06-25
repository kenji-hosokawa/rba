// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_stateValue_Sound.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_stateValue_Sound.hpp"

namespace {

using namespace rba;

HA762_stateValue_Sound::HA762_stateValue_Sound() {}
HA762_stateValue_Sound::~HA762_stateValue_Sound() {}

void HA762_stateValue_Sound::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_stateValue_Sound::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_stateValue_Sound::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_stateValue_Sound::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_stateValue_Sound::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_stateValue_Sound::getAllocated(const std::string& msg,
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

bool HA762_stateValue_Sound::isCanceled(const std::string& msg,
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

bool HA762_stateValue_Sound::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_stateValue_Sound::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_stateValue_Sound::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_stateValue_Sound::isEnableContext(const std::string& msg,
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

bool HA762_stateValue_Sound::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_stateValue_Sound::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_stateValue_Sound, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,a1,S2
  result_ = arb_->execute(u8"a1/S2", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=5", u8"A"));
  EXPECT_FALSE(isAttenuated("line=5", u8"A"));
  // 0006  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=6", u8"B"));
  // 0007  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=7", u8"C"));
  // 0008  Assert,A,D,,attenuated:true
  EXPECT_EQ(u8"",getAllocated("line=8", u8"D"));
}

// 0010  #start 2
TEST_F(HA762_stateValue_Sound, Test_02)
{
  std::list<std::string> contexts;

  // 0011  CL
  arb_->clearArbitration();
  // 0012  C,on,d1,S1
  result_ = arb_->execute(u8"d1/S1", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=13"));
  EXPECT_TRUE(isSatisfiedConstraints("line=13"));
  // 0014  Assert,A,A,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=14", u8"A"));
  // 0015  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=15", u8"B"));
  // 0016  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=16", u8"C"));
  // 0017  Assert,A,D,d1,attenuated:true
  EXPECT_EQ(u8"d1",getAllocated("line=17", u8"D"));
  EXPECT_TRUE(isAttenuated("line=17", u8"D"));
}

// 0019  #start 3
TEST_F(HA762_stateValue_Sound, Test_03)
{
  std::list<std::string> contexts;

  // 0020  CL
  arb_->clearArbitration();
  // 0021  C,on,a1,S1
  result_ = arb_->execute(u8"a1/S1", true);
  EXPECT_TRUE(isSuccess("line=21"));
  EXPECT_TRUE(isSatisfiedConstraints("line=21"));
  // 0022  C,on,b1,S1
  result_ = arb_->execute(u8"b1/S1", true);
  EXPECT_TRUE(isSuccess("line=22"));
  EXPECT_TRUE(isSatisfiedConstraints("line=22"));
  // 0023  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=23"));
  EXPECT_TRUE(isSatisfiedConstraints("line=23"));
  // 0024  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=24", u8"A"));
  EXPECT_FALSE(isAttenuated("line=24", u8"A"));
  // 0025  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=25", u8"B"));
  // 0026  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=26", u8"C"));
  // 0027  Assert,A,D,,attenuated:true
  EXPECT_EQ(u8"",getAllocated("line=27", u8"D"));
}

// 0029  #start 4
TEST_F(HA762_stateValue_Sound, Test_04)
{
  std::list<std::string> contexts;

  // 0030  CL
  arb_->clearArbitration();
  // 0031  C,on,a1,S2
  result_ = arb_->execute(u8"a1/S2", true);
  EXPECT_TRUE(isSuccess("line=31"));
  EXPECT_TRUE(isSatisfiedConstraints("line=31"));
  // 0032  C,on,a2,S1
  result_ = arb_->execute(u8"a2/S1", true);
  EXPECT_TRUE(isSuccess("line=32"));
  EXPECT_TRUE(isSatisfiedConstraints("line=32"));
  // 0033  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,a2,attenuated:false
  EXPECT_EQ(u8"a2",getAllocated("line=34", u8"A"));
  EXPECT_FALSE(isAttenuated("line=34", u8"A"));
  // 0035  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=36", u8"C"));
  // 0037  Assert,A,D,,attenuated:true
  EXPECT_EQ(u8"",getAllocated("line=37", u8"D"));
}

// 0039  #start 5
TEST_F(HA762_stateValue_Sound, Test_05)
{
  std::list<std::string> contexts;

  // 0040  CL
  arb_->clearArbitration();
  // 0041  C,on,a1,S3
  result_ = arb_->execute(u8"a1/S3", true);
  EXPECT_TRUE(isSuccess("line=41"));
  EXPECT_TRUE(isSatisfiedConstraints("line=41"));
  // 0042  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=42"));
  EXPECT_TRUE(isSatisfiedConstraints("line=42"));
  // 0043  Assert,A,A,a1,attenuated:false
  EXPECT_EQ(u8"a1",getAllocated("line=43", u8"A"));
  EXPECT_FALSE(isAttenuated("line=43", u8"A"));
  // 0044  Assert,A,B,,attenuated:false
  EXPECT_EQ(u8"",getAllocated("line=44", u8"B"));
  // 0045  Assert,A,C,c1,attenuated:false
  EXPECT_EQ(u8"c1",getAllocated("line=45", u8"C"));
  EXPECT_FALSE(isAttenuated("line=45", u8"C"));
  // 0046  Assert,A,D,,attenuated:true
  EXPECT_EQ(u8"",getAllocated("line=46", u8"D"));
}

}

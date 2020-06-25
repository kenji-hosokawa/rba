// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_stateValue.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_stateValue.hpp"

namespace {

using namespace rba;

HA762_stateValue::HA762_stateValue() {}
HA762_stateValue::~HA762_stateValue() {}

void HA762_stateValue::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_stateValue::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_stateValue::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_stateValue::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_stateValue::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_stateValue::getAllocated(const std::string& msg,
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

bool HA762_stateValue::isCanceled(const std::string& msg,
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

bool HA762_stateValue::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_stateValue::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_stateValue::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_stateValue::isEnableContext(const std::string& msg,
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

bool HA762_stateValue::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_stateValue::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_stateValue, Test_01)
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
  // 0005  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=5", u8"A"));
  // 0006  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"B"));
  // 0007  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"C"));
}

// 0009  #start 2
TEST_F(HA762_stateValue, Test_02)
{
  std::list<std::string> contexts;

  // 0010  CL
  arb_->clearArbitration();
  // 0011  C,on,a1,S1
  result_ = arb_->execute(u8"a1/S1", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  C,on,b1,S1
  result_ = arb_->execute(u8"b1/S1", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=13"));
  EXPECT_TRUE(isSatisfiedConstraints("line=13"));
  // 0014  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=14", u8"A"));
  // 0015  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"B"));
  // 0016  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"C"));
}

// 0018  #start 3
TEST_F(HA762_stateValue, Test_03)
{
  std::list<std::string> contexts;

  // 0019  CL
  arb_->clearArbitration();
  // 0020  C,on,a1,S2
  result_ = arb_->execute(u8"a1/S2", true);
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  C,on,a2,S1
  result_ = arb_->execute(u8"a2/S1", true);
  EXPECT_TRUE(isSuccess("line=21"));
  EXPECT_TRUE(isSatisfiedConstraints("line=21"));
  // 0022  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=22"));
  EXPECT_TRUE(isSatisfiedConstraints("line=22"));
  // 0023  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=23", u8"A"));
  // 0024  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=24", u8"B"));
  // 0025  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"C"));
}

// 0027  #start 4
TEST_F(HA762_stateValue, Test_04)
{
  std::list<std::string> contexts;

  // 0028  CL
  arb_->clearArbitration();
  // 0029  C,on,a1,S3
  result_ = arb_->execute(u8"a1/S3", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  C,on,c1,S1
  result_ = arb_->execute(u8"c1/S1", true);
  EXPECT_TRUE(isSuccess("line=30"));
  EXPECT_TRUE(isSatisfiedConstraints("line=30"));
  // 0031  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=31", u8"A"));
  // 0032  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=32", u8"B"));
  // 0033  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=33", u8"C"));
}

}

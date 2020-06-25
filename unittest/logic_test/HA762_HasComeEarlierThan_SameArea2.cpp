// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_HasComeEarlierThan_SameArea2.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_HasComeEarlierThan_SameArea2.hpp"

namespace {

using namespace rba;

HA762_HasComeEarlierThan_SameArea2::HA762_HasComeEarlierThan_SameArea2() {}
HA762_HasComeEarlierThan_SameArea2::~HA762_HasComeEarlierThan_SameArea2() {}

void HA762_HasComeEarlierThan_SameArea2::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_HasComeEarlierThan_SameArea2::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_HasComeEarlierThan_SameArea2::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_HasComeEarlierThan_SameArea2::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_HasComeEarlierThan_SameArea2::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_HasComeEarlierThan_SameArea2::getAllocated(const std::string& msg,
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

bool HA762_HasComeEarlierThan_SameArea2::isCanceled(const std::string& msg,
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

bool HA762_HasComeEarlierThan_SameArea2::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_HasComeEarlierThan_SameArea2::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_HasComeEarlierThan_SameArea2::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_HasComeEarlierThan_SameArea2::isEnableContext(const std::string& msg,
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

bool HA762_HasComeEarlierThan_SameArea2::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_HasComeEarlierThan_SameArea2::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_HasComeEarlierThan_SameArea2, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,a3,NORMAL
  result_ = arb_->execute(u8"a3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,a3
  EXPECT_EQ(u8"a3",getAllocated("line=4", u8"A"));
  // 0005  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"B"));
  // 0006  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=6", u8"a1"));
  // 0007  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=7", u8"a2"));
  // 0008  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=8", u8"a3"));
  // 0009  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=9", u8"b1"));
  // 0010  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=10", u8"b2"));
  // 0011  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=11", u8"b3"));
}

// 0013  #start 2
TEST_F(HA762_HasComeEarlierThan_SameArea2, Test_02)
{
  std::list<std::string> contexts;

  // 0014  CL
  arb_->clearArbitration();
  // 0015  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"A"));
  // 0017  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=17", u8"B"));
  // 0018  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=18", u8"a1"));
  // 0019  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=19", u8"a2"));
  // 0020  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=20", u8"a3"));
  // 0021  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=21", u8"b1"));
  // 0022  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=22", u8"b2"));
  // 0023  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=23", u8"b3"));
  // 0024  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=24"));
  EXPECT_TRUE(isSatisfiedConstraints("line=24"));
  // 0025  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"A"));
  // 0026  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=26", u8"B"));
  // 0027  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=27", u8"a1"));
  // 0028  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=28", u8"a2"));
  // 0029  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=29", u8"a3"));
  // 0030  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=30", u8"b1"));
  // 0031  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=31", u8"b2"));
  // 0032  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=32", u8"b3"));
  // 0033  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"B"));
  // 0036  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=36", u8"a1"));
  // 0037  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=37", u8"a2"));
  // 0038  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=38", u8"a3"));
  // 0039  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=39", u8"b1"));
  // 0040  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=40", u8"b2"));
  // 0041  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=41", u8"b3"));
}

// 0043  #start 3
TEST_F(HA762_HasComeEarlierThan_SameArea2, Test_03)
{
  std::list<std::string> contexts;

  // 0044  CL
  arb_->clearArbitration();
  // 0045  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=45"));
  EXPECT_TRUE(isSatisfiedConstraints("line=45"));
  // 0046  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=46", u8"A"));
  // 0047  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=47", u8"B"));
  // 0048  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=48", u8"a1"));
  // 0049  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=49", u8"a2"));
  // 0050  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=50", u8"a3"));
  // 0051  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=51", u8"b1"));
  // 0052  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=52", u8"b2"));
  // 0053  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=53", u8"b3"));
  // 0054  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=54"));
  EXPECT_TRUE(isSatisfiedConstraints("line=54"));
  // 0055  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=55", u8"A"));
  // 0056  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=56", u8"B"));
  // 0057  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=57", u8"a1"));
  // 0058  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=58", u8"a2"));
  // 0059  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=59", u8"a3"));
  // 0060  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=60", u8"b1"));
  // 0061  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=61", u8"b2"));
  // 0062  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=62", u8"b3"));
  // 0063  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=63"));
  EXPECT_TRUE(isSatisfiedConstraints("line=63"));
  // 0064  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=64", u8"A"));
  // 0065  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=65", u8"B"));
  // 0066  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=66", u8"a1"));
  // 0067  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=67", u8"a2"));
  // 0068  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=68", u8"a3"));
  // 0069  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=69", u8"b1"));
  // 0070  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=70", u8"b2"));
  // 0071  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=71", u8"b3"));
}

}

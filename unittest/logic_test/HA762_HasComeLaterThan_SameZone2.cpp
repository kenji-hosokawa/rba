// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_HasComeLaterThan_SameZone2.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_HasComeLaterThan_SameZone2.hpp"

namespace {

using namespace rba;

HA762_HasComeLaterThan_SameZone2::HA762_HasComeLaterThan_SameZone2() {}
HA762_HasComeLaterThan_SameZone2::~HA762_HasComeLaterThan_SameZone2() {}

void HA762_HasComeLaterThan_SameZone2::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_HasComeLaterThan_SameZone2::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_HasComeLaterThan_SameZone2::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_HasComeLaterThan_SameZone2::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_HasComeLaterThan_SameZone2::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_HasComeLaterThan_SameZone2::getAllocated(const std::string& msg,
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

bool HA762_HasComeLaterThan_SameZone2::isCanceled(const std::string& msg,
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

bool HA762_HasComeLaterThan_SameZone2::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_HasComeLaterThan_SameZone2::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_HasComeLaterThan_SameZone2::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_HasComeLaterThan_SameZone2::isEnableContext(const std::string& msg,
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

bool HA762_HasComeLaterThan_SameZone2::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_HasComeLaterThan_SameZone2::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_HasComeLaterThan_SameZone2, Test_01)
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
TEST_F(HA762_HasComeLaterThan_SameZone2, Test_02)
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
  // 0024  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=24"));
  EXPECT_TRUE(isSatisfiedConstraints("line=24"));
  // 0025  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=25"));
  EXPECT_TRUE(isSatisfiedConstraints("line=25"));
  // 0026  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=26", u8"A"));
  // 0027  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=27", u8"B"));
  // 0028  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=28", u8"a1"));
  // 0029  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=29", u8"a2"));
  // 0030  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=30", u8"a3"));
  // 0031  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=31", u8"b1"));
  // 0032  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=32", u8"b2"));
  // 0033  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=33", u8"b3"));
}

// 0035  #start 3
TEST_F(HA762_HasComeLaterThan_SameZone2, Test_03)
{
  std::list<std::string> contexts;

  // 0036  CL
  arb_->clearArbitration();
  // 0037  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=37"));
  EXPECT_TRUE(isSatisfiedConstraints("line=37"));
  // 0038  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=38", u8"A"));
  // 0039  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=39", u8"B"));
  // 0040  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=40", u8"a1"));
  // 0041  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=41", u8"a2"));
  // 0042  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=42", u8"a3"));
  // 0043  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=43", u8"b1"));
  // 0044  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=44", u8"b2"));
  // 0045  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=45", u8"b3"));
  // 0046  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=46"));
  EXPECT_TRUE(isSatisfiedConstraints("line=46"));
  // 0047  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=47"));
  EXPECT_TRUE(isSatisfiedConstraints("line=47"));
  // 0048  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=48", u8"A"));
  // 0049  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=49", u8"B"));
  // 0050  Assert,C,isCanceled,a1,false
  EXPECT_FALSE(isCanceled("line=50", u8"a1"));
  // 0051  Assert,C,isCanceled,a2,false
  EXPECT_FALSE(isCanceled("line=51", u8"a2"));
  // 0052  Assert,C,isCanceled,a3,false
  EXPECT_FALSE(isCanceled("line=52", u8"a3"));
  // 0053  Assert,C,isCanceled,b1,false
  EXPECT_FALSE(isCanceled("line=53", u8"b1"));
  // 0054  Assert,C,isCanceled,b2,false
  EXPECT_FALSE(isCanceled("line=54", u8"b2"));
  // 0055  Assert,C,isCanceled,b3,false
  EXPECT_FALSE(isCanceled("line=55", u8"b3"));
}

}

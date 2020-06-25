// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA2075_affectedAllocatable.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA2075_affectedAllocatable.hpp"


namespace {

using namespace rba;

HA2075_affectedAllocatable::HA2075_affectedAllocatable() {}
HA2075_affectedAllocatable::~HA2075_affectedAllocatable() {}

void HA2075_affectedAllocatable::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA2075_affectedAllocatable::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA2075_affectedAllocatable::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA2075_affectedAllocatable::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA2075_affectedAllocatable::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA2075_affectedAllocatable::getAllocated(const std::string& msg,
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

bool HA2075_affectedAllocatable::isCanceled(const std::string& msg,
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

bool HA2075_affectedAllocatable::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA2075_affectedAllocatable::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA2075_affectedAllocatable::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA2075_affectedAllocatable::isEnableContext(const std::string& msg,
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

bool HA2075_affectedAllocatable::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA2075_affectedAllocatable::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA2075_affectedAllocatable, Test_01)
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
  // 0006  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"B"));
}

// 0008  #start 2
TEST_F(HA2075_affectedAllocatable, Test_02)
{
  std::list<std::string> contexts;
  // 0009  CL
  arb_->clearArbitration();
  // 0010  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=10"));
  EXPECT_TRUE(isSatisfiedConstraints("line=10"));
  // 0011  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=12", u8"A"));
  // 0013  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=13", u8"B"));
}

// 0015  #start 3
TEST_F(HA2075_affectedAllocatable, Test_03)
{
  std::list<std::string> contexts;
  // 0016  CL
  arb_->clearArbitration();
  // 0017  C,on,A3,NORMAL
  result_ = arb_->execute(u8"A3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,B2,NORMAL
  result_ = arb_->execute(u8"B2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,A,A3
  EXPECT_EQ(u8"A3",getAllocated("line=19", u8"A"));
  // 0020  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=20", u8"B"));
}

// 0022  #start 4
TEST_F(HA2075_affectedAllocatable, Test_04)
{
  std::list<std::string> contexts;
  // 0023  CL
  arb_->clearArbitration();
  // 0024  C,on,B2,NORMAL
  result_ = arb_->execute(u8"B2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=24"));
  EXPECT_TRUE(isSatisfiedConstraints("line=24"));
  // 0025  C,on,A3,NORMAL
  result_ = arb_->execute(u8"A3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=25"));
  EXPECT_TRUE(isSatisfiedConstraints("line=25"));
  // 0026  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"A"));
  // 0027  Assert,A,B,B2
  EXPECT_EQ(u8"B2",getAllocated("line=27", u8"B"));
}

}

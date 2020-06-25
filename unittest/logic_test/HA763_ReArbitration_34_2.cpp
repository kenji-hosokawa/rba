// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA763_ReArbitration_34_2.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA763_ReArbitration_34_2.hpp"

namespace {

using namespace rba;

HA763_ReArbitration_34_2::HA763_ReArbitration_34_2() {}
HA763_ReArbitration_34_2::~HA763_ReArbitration_34_2() {}

void HA763_ReArbitration_34_2::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA763_ReArbitration_34_2::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA763_ReArbitration_34_2::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA763_ReArbitration_34_2::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA763_ReArbitration_34_2::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA763_ReArbitration_34_2::getAllocated(const std::string& msg,
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

bool HA763_ReArbitration_34_2::isCanceled(const std::string& msg,
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

bool HA763_ReArbitration_34_2::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA763_ReArbitration_34_2::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA763_ReArbitration_34_2::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA763_ReArbitration_34_2::isEnableContext(const std::string& msg,
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

bool HA763_ReArbitration_34_2::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA763_ReArbitration_34_2::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA763_ReArbitration_34_2, Test_01)
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
  // 0005  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  // 0006  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=6"));
  EXPECT_TRUE(isSatisfiedConstraints("line=6"));
  // 0007  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=7", u8"A"));
  // 0008  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"B"));
  // 0009  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=9", u8"C"));
  // 0010  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=10", u8"D"));
}

}

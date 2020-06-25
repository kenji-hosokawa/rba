// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1516_select_size.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1516_select_size.hpp"


namespace {

using namespace rba;

HA1516_select_size::HA1516_select_size() {}
HA1516_select_size::~HA1516_select_size() {}

void HA1516_select_size::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1516_select_size::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1516_select_size::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1516_select_size::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1516_select_size::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1516_select_size::getAllocated(const std::string& msg,
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

bool HA1516_select_size::isCanceled(const std::string& msg,
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

bool HA1516_select_size::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1516_select_size::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1516_select_size::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1516_select_size::isEnableContext(const std::string& msg,
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

bool HA1516_select_size::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1516_select_size::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 0
TEST_F(HA1516_select_size, Test_00)
{
  std::list<std::string> contexts;
  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"A"));
  // 0005  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"B"));
  // 0006  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"C"));
}

// 0008  #start 1
TEST_F(HA1516_select_size, Test_01)
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
  // 0014  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"C"));
}

// 0016  #start 3
TEST_F(HA1516_select_size, Test_03)
{
  std::list<std::string> contexts;
  // 0017  CL
  arb_->clearArbitration();
  // 0018  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=21", u8"A"));
  // 0022  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=22", u8"B"));
  // 0023  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=23", u8"C"));
}

}

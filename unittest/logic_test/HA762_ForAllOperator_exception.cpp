// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_ForAllOperator_exception.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_ForAllOperator_exception.hpp"

namespace {

using namespace rba;

HA762_ForAllOperator_exception::HA762_ForAllOperator_exception() {}
HA762_ForAllOperator_exception::~HA762_ForAllOperator_exception() {}

void HA762_ForAllOperator_exception::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_ForAllOperator_exception::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_ForAllOperator_exception::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_ForAllOperator_exception::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_ForAllOperator_exception::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_ForAllOperator_exception::getAllocated(const std::string& msg,
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

bool HA762_ForAllOperator_exception::isCanceled(const std::string& msg,
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

bool HA762_ForAllOperator_exception::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_ForAllOperator_exception::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_ForAllOperator_exception::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_ForAllOperator_exception::isEnableContext(const std::string& msg,
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

bool HA762_ForAllOperator_exception::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_ForAllOperator_exception::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_ForAllOperator_exception, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,コンテンツA1,NORMAL
  result_ = arb_->execute(u8"コンテンツA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"エリアA"));
  // 0005  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"エリアB"));
  // 0006  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"エリアC"));
  // 0007  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"エリアD"));
  // 0008  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"エリアE"));
  // 0009  C,on,コンテンツC1,NORMAL
  result_ = arb_->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=9"));
  EXPECT_TRUE(isSatisfiedConstraints("line=9"));
  // 0010  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=10", u8"エリアA"));
  // 0011  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"エリアB"));
  // 0012  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=12", u8"エリアC"));
  // 0013  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"エリアD"));
  // 0014  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"エリアE"));
  // 0015  C,on,コンテンツE1,NORMAL
  result_ = arb_->execute(u8"コンテンツE1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"エリアA"));
  // 0017  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=17", u8"エリアB"));
  // 0018  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=18", u8"エリアC"));
  // 0019  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=19", u8"エリアD"));
  // 0020  Assert,A,エリアE,コンテンツE1
  EXPECT_EQ(u8"コンテンツE1",getAllocated("line=20", u8"エリアE"));
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_ObjectCompare_exception.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_ObjectCompare_exception.hpp"

namespace {

using namespace rba;

HA762_ObjectCompare_exception::HA762_ObjectCompare_exception() {}
HA762_ObjectCompare_exception::~HA762_ObjectCompare_exception() {}

void HA762_ObjectCompare_exception::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_ObjectCompare_exception::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_ObjectCompare_exception::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_ObjectCompare_exception::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_ObjectCompare_exception::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_ObjectCompare_exception::getAllocated(const std::string& msg,
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

bool HA762_ObjectCompare_exception::isCanceled(const std::string& msg,
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

bool HA762_ObjectCompare_exception::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_ObjectCompare_exception::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_ObjectCompare_exception::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_ObjectCompare_exception::isEnableContext(const std::string& msg,
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

bool HA762_ObjectCompare_exception::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_ObjectCompare_exception::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_ObjectCompare_exception, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,コンテンツC1,NORMAL
  result_ = arb_->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"エリアA"));
  // 0005  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"エリアB"));
  // 0006  Assert,A,エリアC,コンテンツC1
  EXPECT_EQ(u8"コンテンツC1",getAllocated("line=6", u8"エリアC"));
  // 0007  C,on,コンテンツA1,NORMAL
  result_ = arb_->execute(u8"コンテンツA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=7"));
  EXPECT_TRUE(isSatisfiedConstraints("line=7"));
  // 0008  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=8", u8"エリアA"));
  // 0009  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=9", u8"エリアB"));
  // 0010  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=10", u8"エリアC"));
}

// 0012  #start 2
TEST_F(HA762_ObjectCompare_exception, Test_02)
{
  std::list<std::string> contexts;

  // 0013  CL
  arb_->clearArbitration();
  // 0014  C,on,コンテンツC1,NORMAL
  result_ = arb_->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=14"));
  EXPECT_TRUE(isSatisfiedConstraints("line=14"));
  // 0015  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"エリアA"));
  // 0016  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"エリアB"));
  // 0017  Assert,A,エリアC,コンテンツC1
  EXPECT_EQ(u8"コンテンツC1",getAllocated("line=17", u8"エリアC"));
  // 0018  C,on,コンテンツB1,NORMAL
  result_ = arb_->execute(u8"コンテンツB1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=19", u8"エリアA"));
  // 0020  Assert,A,エリアB,コンテンツB1
  EXPECT_EQ(u8"コンテンツB1",getAllocated("line=20", u8"エリアB"));
  // 0021  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=21", u8"エリアC"));
}

// 0023  #start 3
TEST_F(HA762_ObjectCompare_exception, Test_03)
{
  std::list<std::string> contexts;

  // 0024  CL
  arb_->clearArbitration();
  // 0025  C,on,コンテンツC1,NORMAL
  result_ = arb_->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=25"));
  EXPECT_TRUE(isSatisfiedConstraints("line=25"));
  // 0026  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"エリアA"));
  // 0027  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=27", u8"エリアB"));
  // 0028  Assert,A,エリアC,コンテンツC1
  EXPECT_EQ(u8"コンテンツC1",getAllocated("line=28", u8"エリアC"));
}

}

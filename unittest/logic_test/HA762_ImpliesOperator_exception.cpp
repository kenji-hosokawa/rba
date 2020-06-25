// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_ImpliesOperator_exception.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_ImpliesOperator_exception.hpp"

namespace {

using namespace rba;

HA762_ImpliesOperator_exception::HA762_ImpliesOperator_exception() {}
HA762_ImpliesOperator_exception::~HA762_ImpliesOperator_exception() {}

void HA762_ImpliesOperator_exception::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_ImpliesOperator_exception::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_ImpliesOperator_exception::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_ImpliesOperator_exception::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_ImpliesOperator_exception::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_ImpliesOperator_exception::getAllocated(const std::string& msg,
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

bool HA762_ImpliesOperator_exception::isCanceled(const std::string& msg,
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

bool HA762_ImpliesOperator_exception::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_ImpliesOperator_exception::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_ImpliesOperator_exception::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_ImpliesOperator_exception::isEnableContext(const std::string& msg,
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

bool HA762_ImpliesOperator_exception::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_ImpliesOperator_exception::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_ImpliesOperator_exception, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,コンテンツA1,NORMAL
  result_ = arb_->execute(u8"コンテンツA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=4", u8"エリアA"));
  // 0005  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"エリアB"));
  // 0006  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"エリアC"));
  // 0007  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"エリアD"));
  // 0008  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"エリアE"));
}

// 0010  #start 2
TEST_F(HA762_ImpliesOperator_exception, Test_02)
{
  std::list<std::string> contexts;

  // 0011  CL
  arb_->clearArbitration();
  // 0012  C,on,コンテンツB1,NORMAL
  result_ = arb_->execute(u8"コンテンツB1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"エリアA"));
  // 0014  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"エリアB"));
  // 0015  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"エリアC"));
  // 0016  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"エリアD"));
  // 0017  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=17", u8"エリアE"));
}

// 0019  #start 3
TEST_F(HA762_ImpliesOperator_exception, Test_03)
{
  std::list<std::string> contexts;

  // 0020  CL
  arb_->clearArbitration();
  // 0021  C,on,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=21"));
  EXPECT_TRUE(isSatisfiedConstraints("line=21"));
  // 0022  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=22", u8"エリアA"));
  // 0023  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=23", u8"エリアB"));
  // 0024  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=24", u8"エリアC"));
  // 0025  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"エリアD"));
  // 0026  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"エリアE"));
}

// 0028  #start 4
TEST_F(HA762_ImpliesOperator_exception, Test_04)
{
  std::list<std::string> contexts;

  // 0029  CL
  arb_->clearArbitration();
  // 0030  C,on,コンテンツB2,NORMAL
  result_ = arb_->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=30"));
  EXPECT_TRUE(isSatisfiedConstraints("line=30"));
  // 0031  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=31", u8"エリアA"));
  // 0032  Assert,A,エリアB,コンテンツB2
  EXPECT_EQ(u8"コンテンツB2",getAllocated("line=32", u8"エリアB"));
  // 0033  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=33", u8"エリアC"));
  // 0034  Assert,A,エリアD,
  EXPECT_EQ(u8"",getAllocated("line=34", u8"エリアD"));
  // 0035  Assert,A,エリアE,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"エリアE"));
}

// 0037  #start 5
TEST_F(HA762_ImpliesOperator_exception, Test_05)
{
  std::list<std::string> contexts;

  // 0038  CL
  arb_->clearArbitration();
  // 0039  C,on,コンテンツC1,NORMAL
  result_ = arb_->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=39"));
  EXPECT_TRUE(isSatisfiedConstraints("line=39"));
  // 0040  C,on,コンテンツD1,NORMAL
  result_ = arb_->execute(u8"コンテンツD1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=40"));
  EXPECT_TRUE(isSatisfiedConstraints("line=40"));
  // 0041  C,on,コンテンツE1,NORMAL
  result_ = arb_->execute(u8"コンテンツE1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=41"));
  EXPECT_TRUE(isSatisfiedConstraints("line=41"));
  // 0042  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=42", u8"エリアA"));
  // 0043  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=43", u8"エリアB"));
  // 0044  Assert,A,エリアC,コンテンツC1
  EXPECT_EQ(u8"コンテンツC1",getAllocated("line=44", u8"エリアC"));
  // 0045  Assert,A,エリアD,コンテンツD1
  EXPECT_EQ(u8"コンテンツD1",getAllocated("line=45", u8"エリアD"));
  // 0046  Assert,A,エリアE,コンテンツE1
  EXPECT_EQ(u8"コンテンツE1",getAllocated("line=46", u8"エリアE"));
}

}

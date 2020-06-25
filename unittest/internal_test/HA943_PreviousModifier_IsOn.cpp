// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA943_PreviousModifier_IsOn.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA943_PreviousModifier_IsOn.hpp"

namespace {

using namespace rba;

HA943_PreviousModifier_IsOn::HA943_PreviousModifier_IsOn() {}
HA943_PreviousModifier_IsOn::~HA943_PreviousModifier_IsOn() {}

void HA943_PreviousModifier_IsOn::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA943_PreviousModifier_IsOn::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA943_PreviousModifier_IsOn::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA943_PreviousModifier_IsOn::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA943_PreviousModifier_IsOn::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA943_PreviousModifier_IsOn::getAllocated(const std::string& msg,
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

bool HA943_PreviousModifier_IsOn::isCanceled(const std::string& msg,
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

bool HA943_PreviousModifier_IsOn::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA943_PreviousModifier_IsOn::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA943_PreviousModifier_IsOn::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA943_PreviousModifier_IsOn::isEnableContext(const std::string& msg,
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

bool HA943_PreviousModifier_IsOn::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA943_PreviousModifier_IsOn::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA943_PreviousModifier_IsOn, Test_01)
{
  std::list<std::string> contexts;
  std::list<std::pair<std::string, std::int32_t>> props;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,コンテンツA1,NORMAL
  result_ = arb_->execute(u8"コンテンツA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,コンテンツB1,NORMAL
  result_ = arb_->execute(u8"コンテンツB1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=5", u8"エリアA"));
  // 0006  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"エリアB"));
  // 0007  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=7", u8"s1_Local"));
  // 0008  C,on,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=8"));
  EXPECT_TRUE(isSatisfiedConstraints("line=8"));
  // 0009  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=9", u8"エリアA"));
  // 0010  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=10", u8"エリアB"));
  // 0011  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=11", u8"s1_Local"));
  // 0012  C,off,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", false);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=13", u8"エリアA"));
  // 0014  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"エリアB"));
  // 0015  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=15", u8"s1_Local"));
  // 0016  S,on,s1_Local
  EXPECT_TRUE(arb_->setScene(u8"s1_Local", true, props));
  // 0017  C,on,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=18", u8"エリアA"));
  // 0019  Assert,A,エリアB,コンテンツB1
  EXPECT_EQ(u8"コンテンツB1",getAllocated("line=19", u8"エリアB"));
  // 0020  Assert,S,s1_Local,off
  EXPECT_TRUE(isActive("line=20", u8"s1_Local"));
  // 0021  C,off,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", false);
  EXPECT_TRUE(isSuccess("line=21"));
  EXPECT_TRUE(isSatisfiedConstraints("line=21"));
  // 0022  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=22", u8"エリアA"));
  // 0023  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=23", u8"エリアB"));
  // 0024  Assert,S,s1_Local,off
  EXPECT_TRUE(isActive("line=24", u8"s1_Local"));
}

// 0026  #start 2
TEST_F(HA943_PreviousModifier_IsOn, Test_02)
{
  std::list<std::string> contexts;

  // 0027  CL
  arb_->clearArbitration();
  // 0028  C,on,コンテンツA1,NORMAL
  result_ = arb_->execute(u8"コンテンツA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=28"));
  EXPECT_TRUE(isSatisfiedConstraints("line=28"));
  // 0029  C,on,コンテンツB1,NORMAL
  result_ = arb_->execute(u8"コンテンツB1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=30", u8"エリアA"));
  // 0031  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=31", u8"エリアB"));
  // 0032  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=32", u8"s1_Local"));
  // 0033  S,on,s1_Local
  result_ = arb_->execute(u8"s1_Local", true);
  EXPECT_TRUE(isSuccess("line=33"));
  // 0034  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=34", u8"エリアA"));
  // 0035  Assert,A,エリアB,コンテンツB1
  EXPECT_EQ(u8"コンテンツB1",getAllocated("line=35", u8"エリアB"));
  // 0036  Assert,S,s1_Local,on
  EXPECT_TRUE(isActive("line=36", u8"s1_Local"));
  // 0037  S,off,s1_Local
  result_ = arb_->execute(u8"s1_Local", false);
  EXPECT_TRUE(isSuccess("line=37"));
  // 0038  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=38", u8"エリアA"));
  // 0039  Assert,A,エリアB,コンテンツB1
  EXPECT_EQ(u8"コンテンツB1",getAllocated("line=39", u8"エリアB"));
  // 0040  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=40", u8"s1_Local"));
  // 0041  C,off,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", false);
  EXPECT_TRUE(isSuccess("line=41"));
  EXPECT_TRUE(isSatisfiedConstraints("line=41"));
  // 0042  Assert,A,エリアA,コンテンツA1
  EXPECT_EQ(u8"コンテンツA1",getAllocated("line=42", u8"エリアA"));
  // 0043  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=43", u8"エリアB"));
  // 0044  Assert,S,s1_Local,off
  EXPECT_FALSE(isActive("line=44", u8"s1_Local"));
}

// 0046  #start 3
TEST_F(HA943_PreviousModifier_IsOn, Test_03)
{
  std::list<std::string> contexts;
  std::list<std::pair<std::string, std::int32_t>> props;

  // 0047  CL
  arb_->clearArbitration();
  // 0048  C,on,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=48"));
  EXPECT_TRUE(isSatisfiedConstraints("line=48"));
  // 0049  C,on,コンテンツB2,NORMAL
  result_ = arb_->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=49"));
  EXPECT_TRUE(isSatisfiedConstraints("line=49"));
  // 0050  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=50", u8"エリアA"));
  // 0051  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=51", u8"エリアB"));
  // 0052  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=52", u8"s2_Global"));
  // 0053  C,on,コンテンツA3,NORMAL
  result_ = arb_->execute(u8"コンテンツA3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=53"));
  EXPECT_TRUE(isSatisfiedConstraints("line=53"));
  // 0054  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=54", u8"エリアA"));
  // 0055  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=55", u8"エリアB"));
  // 0056  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=56", u8"s2_Global"));
  // 0057  C,off,コンテンツA3,NORMAL
  result_ = arb_->execute(u8"コンテンツA3/NORMAL", false);
  EXPECT_TRUE(isSuccess("line=57"));
  EXPECT_TRUE(isSatisfiedConstraints("line=57"));
  // 0058  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=58", u8"エリアA"));
  // 0059  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=59", u8"エリアB"));
  // 0060  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=60", u8"s2_Global"));
  // 0061  S,on,s2_Global
  EXPECT_TRUE(arb_->setScene(u8"s2_Global", true, props));
  // 0062  C,on,コンテンツA3,NORMAL
  result_ = arb_->execute(u8"コンテンツA3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=62"));
  EXPECT_TRUE(isSatisfiedConstraints("line=62"));
  // 0063  Assert,A,エリアA,コンテンツA3
  EXPECT_EQ(u8"コンテンツA3",getAllocated("line=63", u8"エリアA"));
  // 0064  Assert,A,エリアB,コンテンツAB2
  EXPECT_EQ(u8"コンテンツB2",getAllocated("line=64", u8"エリアB"));
  // 0065  Assert,S,s2_Global,on
  EXPECT_TRUE(isActive("line=65", u8"s2_Global"));
  // 0066  C,off,コンテンツA3,NORMAL
  result_ = arb_->execute(u8"コンテンツA3/NORMAL", false);
  EXPECT_TRUE(isSuccess("line=66"));
  EXPECT_TRUE(isSatisfiedConstraints("line=66"));
  // 0067  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=67", u8"エリアA"));
  // 0068  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=68", u8"エリアB"));
  // 0069  Assert,S,s2_Global,on
  EXPECT_TRUE(isActive("line=69", u8"s2_Global"));
}

// 0071  #start 4
TEST_F(HA943_PreviousModifier_IsOn, Test_04)
{
  std::list<std::string> contexts;

  // 0072  CL
  arb_->clearArbitration();
  // 0073  C,on,コンテンツA2,NORMAL
  result_ = arb_->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=73"));
  EXPECT_TRUE(isSatisfiedConstraints("line=73"));
  // 0074  C,on,コンテンツB2,NORMAL
  result_ = arb_->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=74"));
  EXPECT_TRUE(isSatisfiedConstraints("line=74"));
  // 0075  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=75", u8"エリアA"));
  // 0076  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=76", u8"エリアB"));
  // 0077  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=77", u8"s2_Global"));
  // 0078  S,on,s2_Global
  result_ = arb_->execute(u8"s2_Global", true);
  EXPECT_TRUE(isSuccess("line=78"));
  // 0079  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=79", u8"エリアA"));
  // 0080  Assert,A,エリアB,コンテンツB2
  EXPECT_EQ(u8"コンテンツB2",getAllocated("line=80", u8"エリアB"));
  // 0081  Assert,S,s2_Global,on
  EXPECT_TRUE(isActive("line=81", u8"s2_Global"));
  // 0082  S,off,s2_Global
  result_ = arb_->execute(u8"s2_Global", false);
  EXPECT_TRUE(isSuccess("line=82"));
  // 0083  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=83", u8"エリアA"));
  // 0084  Assert,A,エリアB,コンテンツB2
  EXPECT_EQ(u8"コンテンツB2",getAllocated("line=84", u8"エリアB"));
  // 0085  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=85", u8"s2_Global"));
  // 0086  C,on,コンテンツA3,NORMAL
  result_ = arb_->execute(u8"コンテンツA3/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=86"));
  EXPECT_TRUE(isSatisfiedConstraints("line=86"));
  // 0087  Assert,A,エリアA,コンテンツA2
  EXPECT_EQ(u8"コンテンツA2",getAllocated("line=87", u8"エリアA"));
  // 0088  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=88", u8"エリアB"));
  // 0089  Assert,S,s2_Global,off
  EXPECT_FALSE(isActive("line=89", u8"s2_Global"));
}

}

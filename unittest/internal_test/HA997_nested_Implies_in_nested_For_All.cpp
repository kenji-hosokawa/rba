// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA997_nested_Implies_in_nested_For_All.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA997_nested_Implies_in_nested_For_All.hpp"

namespace {

using namespace rba;

HA997_nested_Implies_in_nested_For_All::HA997_nested_Implies_in_nested_For_All() {}
HA997_nested_Implies_in_nested_For_All::~HA997_nested_Implies_in_nested_For_All() {}

void HA997_nested_Implies_in_nested_For_All::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA997_nested_Implies_in_nested_For_All::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA997_nested_Implies_in_nested_For_All::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA997_nested_Implies_in_nested_For_All::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA997_nested_Implies_in_nested_For_All::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA997_nested_Implies_in_nested_For_All::getAllocated(const std::string& msg,
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

bool HA997_nested_Implies_in_nested_For_All::isCanceled(const std::string& msg,
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

bool HA997_nested_Implies_in_nested_For_All::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA997_nested_Implies_in_nested_For_All::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA997_nested_Implies_in_nested_For_All::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA997_nested_Implies_in_nested_For_All::isEnableContext(const std::string& msg,
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

bool HA997_nested_Implies_in_nested_For_All::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA997_nested_Implies_in_nested_For_All::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 a1.NORMAL,b1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"エリアA"));
  // 0006  Assert,A,エリアB,b1
  EXPECT_EQ(u8"b1",getAllocated("line=6", u8"エリアB"));
  // 0007  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"エリアC"));
}

// 0009  #start 2 a1.NORMAL,c1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_02)
{
  std::list<std::string> contexts;

  // 0010  CL
  arb_->clearArbitration();
  // 0011  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"エリアA"));
  // 0014  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"エリアB"));
  // 0015  Assert,A,エリアC,c1
  EXPECT_EQ(u8"c1",getAllocated("line=15", u8"エリアC"));
}

// 0017  #start 3 b1.NORMAL,a1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_03)
{
  std::list<std::string> contexts;

  // 0018  CL
  arb_->clearArbitration();
  // 0019  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  Assert,A,エリアA,a1
  EXPECT_EQ(u8"a1",getAllocated("line=21", u8"エリアA"));
  // 0022  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=22", u8"エリアB"));
  // 0023  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=23", u8"エリアC"));
}

// 0025  #start 4 b1.NORMAL,c1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_04)
{
  std::list<std::string> contexts;

  // 0026  CL
  arb_->clearArbitration();
  // 0027  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=27"));
  EXPECT_TRUE(isSatisfiedConstraints("line=27"));
  // 0028  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=28"));
  EXPECT_TRUE(isSatisfiedConstraints("line=28"));
  // 0029  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=29", u8"エリアA"));
  // 0030  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=30", u8"エリアB"));
  // 0031  Assert,A,エリアC,c1
  EXPECT_EQ(u8"c1",getAllocated("line=31", u8"エリアC"));
}

// 0033  #start 5 c1.NORMAL,a1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_05)
{
  std::list<std::string> contexts;

  // 0034  CL
  arb_->clearArbitration();
  // 0035  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=35"));
  EXPECT_TRUE(isSatisfiedConstraints("line=35"));
  // 0036  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=36"));
  EXPECT_TRUE(isSatisfiedConstraints("line=36"));
  // 0037  Assert,A,エリアA,a1
  EXPECT_EQ(u8"a1",getAllocated("line=37", u8"エリアA"));
  // 0038  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=38", u8"エリアB"));
  // 0039  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=39", u8"エリアC"));
}

// 0041  #start 6 c1.NORMAL,b1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_06)
{
  std::list<std::string> contexts;

  // 0042  CL
  arb_->clearArbitration();
  // 0043  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=43"));
  EXPECT_TRUE(isSatisfiedConstraints("line=43"));
  // 0044  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=44"));
  EXPECT_TRUE(isSatisfiedConstraints("line=44"));
  // 0045  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=45", u8"エリアA"));
  // 0046  Assert,A,エリアB,b1
  EXPECT_EQ(u8"b1",getAllocated("line=46", u8"エリアB"));
  // 0047  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=47", u8"エリアC"));
}

// 0049  #start 7 a1.NORMAL,b1.NORMAL,c1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_07)
{
  std::list<std::string> contexts;

  // 0050  CL
  arb_->clearArbitration();
  // 0051  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=51"));
  EXPECT_TRUE(isSatisfiedConstraints("line=51"));
  // 0052  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=52"));
  EXPECT_TRUE(isSatisfiedConstraints("line=52"));
  // 0053  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=53"));
  EXPECT_TRUE(isSatisfiedConstraints("line=53"));
  // 0054  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=54", u8"エリアA"));
  // 0055  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=55", u8"エリアB"));
  // 0056  Assert,A,エリアC,c1
  EXPECT_EQ(u8"c1",getAllocated("line=56", u8"エリアC"));
}

// 0058  #start 8 a1.NORMAL,c1.NORMAL,b1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_08)
{
  std::list<std::string> contexts;

  // 0059  CL
  arb_->clearArbitration();
  // 0060  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=60"));
  EXPECT_TRUE(isSatisfiedConstraints("line=60"));
  // 0061  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=61"));
  EXPECT_TRUE(isSatisfiedConstraints("line=61"));
  // 0062  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=62"));
  EXPECT_TRUE(isSatisfiedConstraints("line=62"));
  // 0063  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=63", u8"エリアA"));
  // 0064  Assert,A,エリアB,b1
  EXPECT_EQ(u8"b1",getAllocated("line=64", u8"エリアB"));
  // 0065  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=65", u8"エリアC"));
}

// 0067  #start 9 b1.NORMAL,a1.NORMAL,b1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_09)
{
  std::list<std::string> contexts;

  // 0068  CL
  arb_->clearArbitration();
  // 0069  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=69"));
  EXPECT_TRUE(isSatisfiedConstraints("line=69"));
  // 0070  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=70"));
  EXPECT_TRUE(isSatisfiedConstraints("line=70"));
  // 0071  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=71"));
  EXPECT_TRUE(isSatisfiedConstraints("line=71"));
  // 0072  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=72", u8"エリアA"));
  // 0073  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=73", u8"エリアB"));
  // 0074  Assert,A,エリアC,c1
  EXPECT_EQ(u8"c1",getAllocated("line=74", u8"エリアC"));
}

// 0076  #start 10 b1.NORMAL,c1.NORMAL,a1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_10)
{
  std::list<std::string> contexts;

  // 0077  CL
  arb_->clearArbitration();
  // 0078  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=78"));
  EXPECT_TRUE(isSatisfiedConstraints("line=78"));
  // 0079  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=79"));
  EXPECT_TRUE(isSatisfiedConstraints("line=79"));
  // 0080  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=80"));
  EXPECT_TRUE(isSatisfiedConstraints("line=80"));
  // 0081  Assert,A,エリアA,a1
  EXPECT_EQ(u8"a1",getAllocated("line=81", u8"エリアA"));
  // 0082  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=82", u8"エリアB"));
  // 0083  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=83", u8"エリアC"));
}

// 0085  #start 11 c1.NORMAL,a1.NORMAL,b1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_11)
{
  std::list<std::string> contexts;

  // 0086  CL
  arb_->clearArbitration();
  // 0087  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=87"));
  EXPECT_TRUE(isSatisfiedConstraints("line=87"));
  // 0088  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=88"));
  EXPECT_TRUE(isSatisfiedConstraints("line=88"));
  // 0089  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=89"));
  EXPECT_TRUE(isSatisfiedConstraints("line=89"));
  // 0090  Assert,A,エリアA,
  EXPECT_EQ(u8"",getAllocated("line=90", u8"エリアA"));
  // 0091  Assert,A,エリアB,b1
  EXPECT_EQ(u8"b1",getAllocated("line=91", u8"エリアB"));
  // 0092  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=92", u8"エリアC"));
}

// 0094  #start 12 c1.NORMAL,b1.NORMAL,a1.NORMAL
TEST_F(HA997_nested_Implies_in_nested_For_All, Test_12)
{
  std::list<std::string> contexts;

  // 0095  CL
  arb_->clearArbitration();
  // 0096  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=96"));
  EXPECT_TRUE(isSatisfiedConstraints("line=96"));
  // 0097  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=97"));
  EXPECT_TRUE(isSatisfiedConstraints("line=97"));
  // 0098  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=98"));
  EXPECT_TRUE(isSatisfiedConstraints("line=98"));
  // 0099  Assert,A,エリアA,a1
  EXPECT_EQ(u8"a1",getAllocated("line=99", u8"エリアA"));
  // 0100  Assert,A,エリアB,
  EXPECT_EQ(u8"",getAllocated("line=100", u8"エリアB"));
  // 0101  Assert,A,エリアC,
  EXPECT_EQ(u8"",getAllocated("line=101", u8"エリアC"));
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_OrOperator.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_OrOperator.hpp"

namespace {

using namespace rba;

HA762_OrOperator::HA762_OrOperator() {}
HA762_OrOperator::~HA762_OrOperator() {}

void HA762_OrOperator::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_OrOperator::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_OrOperator::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_OrOperator::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_OrOperator::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_OrOperator::getAllocated(const std::string& msg,
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

bool HA762_OrOperator::isCanceled(const std::string& msg,
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

bool HA762_OrOperator::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_OrOperator::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_OrOperator::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_OrOperator::isEnableContext(const std::string& msg,
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

bool HA762_OrOperator::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_OrOperator::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_OrOperator, Test_01)
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
  // 0005  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  // 0006  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=6"));
  EXPECT_TRUE(isSatisfiedConstraints("line=6"));
  // 0007  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=7"));
  EXPECT_TRUE(isSatisfiedConstraints("line=7"));
  // 0008  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=8", u8"A"));
  // 0009  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=9", u8"B"));
  // 0010  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=10", u8"C"));
  // 0011  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"D"));
  // 0012  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=12", u8"E"));
}

// 0014  #start 2
TEST_F(HA762_OrOperator, Test_02)
{
  std::list<std::string> contexts;

  // 0015  CL
  arb_->clearArbitration();
  // 0016  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=16"));
  EXPECT_TRUE(isSatisfiedConstraints("line=16"));
  // 0017  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=21", u8"A"));
  // 0022  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=22", u8"B"));
  // 0023  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=23", u8"C"));
  // 0024  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=24", u8"D"));
  // 0025  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=25", u8"E"));
}

// 0027  #start 3
TEST_F(HA762_OrOperator, Test_03)
{
  std::list<std::string> contexts;

  // 0028  CL
  arb_->clearArbitration();
  // 0029  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=30"));
  EXPECT_TRUE(isSatisfiedConstraints("line=30"));
  // 0031  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=31"));
  EXPECT_TRUE(isSatisfiedConstraints("line=31"));
  // 0032  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=32"));
  EXPECT_TRUE(isSatisfiedConstraints("line=32"));
  // 0033  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=36", u8"C"));
  // 0037  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=37", u8"D"));
  // 0038  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=38", u8"E"));
}

// 0040  #start 4
TEST_F(HA762_OrOperator, Test_04)
{
  std::list<std::string> contexts;

  // 0041  CL
  arb_->clearArbitration();
  // 0042  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=42"));
  EXPECT_TRUE(isSatisfiedConstraints("line=42"));
  // 0043  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=43"));
  EXPECT_TRUE(isSatisfiedConstraints("line=43"));
  // 0044  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=44"));
  EXPECT_TRUE(isSatisfiedConstraints("line=44"));
  // 0045  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=45"));
  EXPECT_TRUE(isSatisfiedConstraints("line=45"));
  // 0046  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=46"));
  EXPECT_TRUE(isSatisfiedConstraints("line=46"));
  // 0047  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=47", u8"A"));
  // 0048  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=48", u8"B"));
  // 0049  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=49", u8"C"));
  // 0050  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=50", u8"D"));
  // 0051  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=51", u8"E"));
}

// 0053  #start 5
TEST_F(HA762_OrOperator, Test_05)
{
  std::list<std::string> contexts;

  // 0054  CL
  arb_->clearArbitration();
  // 0055  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=55"));
  EXPECT_TRUE(isSatisfiedConstraints("line=55"));
  // 0056  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=56"));
  EXPECT_TRUE(isSatisfiedConstraints("line=56"));
  // 0057  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=57"));
  EXPECT_TRUE(isSatisfiedConstraints("line=57"));
  // 0058  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=58"));
  EXPECT_TRUE(isSatisfiedConstraints("line=58"));
  // 0059  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=59"));
  EXPECT_TRUE(isSatisfiedConstraints("line=59"));
  // 0060  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=60", u8"A"));
  // 0061  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=61", u8"B"));
  // 0062  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=62", u8"C"));
  // 0063  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=63", u8"D"));
  // 0064  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=64", u8"E"));
}

// 0066  #start 6
TEST_F(HA762_OrOperator, Test_06)
{
  std::list<std::string> contexts;

  // 0067  CL
  arb_->clearArbitration();
  // 0068  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=68"));
  EXPECT_TRUE(isSatisfiedConstraints("line=68"));
  // 0069  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=69"));
  EXPECT_TRUE(isSatisfiedConstraints("line=69"));
  // 0070  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=70"));
  EXPECT_TRUE(isSatisfiedConstraints("line=70"));
  // 0071  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=71"));
  EXPECT_TRUE(isSatisfiedConstraints("line=71"));
  // 0072  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=72"));
  EXPECT_TRUE(isSatisfiedConstraints("line=72"));
  // 0073  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=73", u8"A"));
  // 0074  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=74", u8"B"));
  // 0075  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=75", u8"C"));
  // 0076  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=76", u8"D"));
  // 0077  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=77", u8"E"));
}

// 0079  #start 7
TEST_F(HA762_OrOperator, Test_07)
{
  std::list<std::string> contexts;

  // 0080  CL
  arb_->clearArbitration();
  // 0081  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=81"));
  EXPECT_TRUE(isSatisfiedConstraints("line=81"));
  // 0082  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=82"));
  EXPECT_TRUE(isSatisfiedConstraints("line=82"));
  // 0083  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=83"));
  EXPECT_TRUE(isSatisfiedConstraints("line=83"));
  // 0084  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=84"));
  EXPECT_TRUE(isSatisfiedConstraints("line=84"));
  // 0085  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=85"));
  EXPECT_TRUE(isSatisfiedConstraints("line=85"));
  // 0086  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=86", u8"A"));
  // 0087  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=87", u8"B"));
  // 0088  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=88", u8"C"));
  // 0089  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=89", u8"D"));
  // 0090  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=90", u8"E"));
}

// 0092  #start 8
TEST_F(HA762_OrOperator, Test_08)
{
  std::list<std::string> contexts;

  // 0093  CL
  arb_->clearArbitration();
  // 0094  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=94"));
  EXPECT_TRUE(isSatisfiedConstraints("line=94"));
  // 0095  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=95"));
  EXPECT_TRUE(isSatisfiedConstraints("line=95"));
  // 0096  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=96"));
  EXPECT_TRUE(isSatisfiedConstraints("line=96"));
  // 0097  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=97"));
  EXPECT_TRUE(isSatisfiedConstraints("line=97"));
  // 0098  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=98"));
  EXPECT_TRUE(isSatisfiedConstraints("line=98"));
  // 0099  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=99", u8"A"));
  // 0100  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=100", u8"B"));
  // 0101  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=101", u8"C"));
  // 0102  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=102", u8"D"));
  // 0103  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=103", u8"E"));
}

// 0105  #start 9
TEST_F(HA762_OrOperator, Test_09)
{
  std::list<std::string> contexts;

  // 0106  CL
  arb_->clearArbitration();
  // 0107  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=107"));
  EXPECT_TRUE(isSatisfiedConstraints("line=107"));
  // 0108  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=108"));
  EXPECT_TRUE(isSatisfiedConstraints("line=108"));
  // 0109  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=109"));
  EXPECT_TRUE(isSatisfiedConstraints("line=109"));
  // 0110  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=110"));
  EXPECT_TRUE(isSatisfiedConstraints("line=110"));
  // 0111  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=111", u8"A"));
  // 0112  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=112", u8"B"));
  // 0113  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=113", u8"C"));
  // 0114  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=114", u8"D"));
  // 0115  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=115", u8"E"));
}

// 0117  #start 10
TEST_F(HA762_OrOperator, Test_10)
{
  std::list<std::string> contexts;

  // 0118  CL
  arb_->clearArbitration();
  // 0119  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=119"));
  EXPECT_TRUE(isSatisfiedConstraints("line=119"));
  // 0120  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=120"));
  EXPECT_TRUE(isSatisfiedConstraints("line=120"));
  // 0121  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=121"));
  EXPECT_TRUE(isSatisfiedConstraints("line=121"));
  // 0122  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=122"));
  EXPECT_TRUE(isSatisfiedConstraints("line=122"));
  // 0123  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=123", u8"A"));
  // 0124  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=124", u8"B"));
  // 0125  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=125", u8"C"));
  // 0126  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=126", u8"D"));
  // 0127  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=127", u8"E"));
}

// 0129  #start 11
TEST_F(HA762_OrOperator, Test_11)
{
  std::list<std::string> contexts;

  // 0130  CL
  arb_->clearArbitration();
  // 0131  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=131"));
  EXPECT_TRUE(isSatisfiedConstraints("line=131"));
  // 0132  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=132"));
  EXPECT_TRUE(isSatisfiedConstraints("line=132"));
  // 0133  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=133"));
  EXPECT_TRUE(isSatisfiedConstraints("line=133"));
  // 0134  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=134"));
  EXPECT_TRUE(isSatisfiedConstraints("line=134"));
  // 0135  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=135", u8"A"));
  // 0136  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=136", u8"B"));
  // 0137  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=137", u8"C"));
  // 0138  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=138", u8"D"));
  // 0139  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=139", u8"E"));
}

// 0141  #start 12
TEST_F(HA762_OrOperator, Test_12)
{
  std::list<std::string> contexts;

  // 0142  CL
  arb_->clearArbitration();
  // 0143  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=143"));
  EXPECT_TRUE(isSatisfiedConstraints("line=143"));
  // 0144  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=144"));
  EXPECT_TRUE(isSatisfiedConstraints("line=144"));
  // 0145  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=145"));
  EXPECT_TRUE(isSatisfiedConstraints("line=145"));
  // 0146  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=146", u8"A"));
  // 0147  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=147", u8"B"));
  // 0148  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=148", u8"C"));
  // 0149  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=149", u8"D"));
  // 0150  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=150", u8"E"));
}

// 0152  #start 13
TEST_F(HA762_OrOperator, Test_13)
{
  std::list<std::string> contexts;

  // 0153  CL
  arb_->clearArbitration();
  // 0154  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=154"));
  EXPECT_TRUE(isSatisfiedConstraints("line=154"));
  // 0155  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=155"));
  EXPECT_TRUE(isSatisfiedConstraints("line=155"));
  // 0156  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=156"));
  EXPECT_TRUE(isSatisfiedConstraints("line=156"));
  // 0157  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=157", u8"A"));
  // 0158  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=158", u8"B"));
  // 0159  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=159", u8"C"));
  // 0160  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=160", u8"D"));
  // 0161  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=161", u8"E"));
}

// 0163  #start 14
TEST_F(HA762_OrOperator, Test_14)
{
  std::list<std::string> contexts;

  // 0164  CL
  arb_->clearArbitration();
  // 0165  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=165"));
  EXPECT_TRUE(isSatisfiedConstraints("line=165"));
  // 0166  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=166"));
  EXPECT_TRUE(isSatisfiedConstraints("line=166"));
  // 0167  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=167"));
  EXPECT_TRUE(isSatisfiedConstraints("line=167"));
  // 0168  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=168", u8"A"));
  // 0169  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=169", u8"B"));
  // 0170  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=170", u8"C"));
  // 0171  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=171", u8"D"));
  // 0172  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=172", u8"E"));
}

// 0174  #start 15
TEST_F(HA762_OrOperator, Test_15)
{
  std::list<std::string> contexts;

  // 0175  CL
  arb_->clearArbitration();
  // 0176  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=176"));
  EXPECT_TRUE(isSatisfiedConstraints("line=176"));
  // 0177  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=177"));
  EXPECT_TRUE(isSatisfiedConstraints("line=177"));
  // 0178  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=178"));
  EXPECT_TRUE(isSatisfiedConstraints("line=178"));
  // 0179  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=179"));
  EXPECT_TRUE(isSatisfiedConstraints("line=179"));
  // 0180  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=180", u8"A"));
  // 0181  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=181", u8"B"));
  // 0182  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=182", u8"C"));
  // 0183  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=183", u8"D"));
  // 0184  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=184", u8"E"));
}

// 0186  #start 16
TEST_F(HA762_OrOperator, Test_16)
{
  std::list<std::string> contexts;

  // 0187  CL
  arb_->clearArbitration();
  // 0188  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=188"));
  EXPECT_TRUE(isSatisfiedConstraints("line=188"));
  // 0189  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=189"));
  EXPECT_TRUE(isSatisfiedConstraints("line=189"));
  // 0190  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=190"));
  EXPECT_TRUE(isSatisfiedConstraints("line=190"));
  // 0191  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=191"));
  EXPECT_TRUE(isSatisfiedConstraints("line=191"));
  // 0192  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=192", u8"A"));
  // 0193  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=193", u8"B"));
  // 0194  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=194", u8"C"));
  // 0195  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=195", u8"D"));
  // 0196  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=196", u8"E"));
}

// 0198  #start 17
TEST_F(HA762_OrOperator, Test_17)
{
  std::list<std::string> contexts;

  // 0199  CL
  arb_->clearArbitration();
  // 0200  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=200"));
  EXPECT_TRUE(isSatisfiedConstraints("line=200"));
  // 0201  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=201"));
  EXPECT_TRUE(isSatisfiedConstraints("line=201"));
  // 0202  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=202"));
  EXPECT_TRUE(isSatisfiedConstraints("line=202"));
  // 0203  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=203"));
  EXPECT_TRUE(isSatisfiedConstraints("line=203"));
  // 0204  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=204", u8"A"));
  // 0205  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=205", u8"B"));
  // 0206  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=206", u8"C"));
  // 0207  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=207", u8"D"));
  // 0208  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=208", u8"E"));
}

// 0210  #start 18
TEST_F(HA762_OrOperator, Test_18)
{
  std::list<std::string> contexts;

  // 0211  CL
  arb_->clearArbitration();
  // 0212  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=212"));
  EXPECT_TRUE(isSatisfiedConstraints("line=212"));
  // 0213  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=213"));
  EXPECT_TRUE(isSatisfiedConstraints("line=213"));
  // 0214  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=214"));
  EXPECT_TRUE(isSatisfiedConstraints("line=214"));
  // 0215  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=215", u8"A"));
  // 0216  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=216", u8"B"));
  // 0217  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=217", u8"C"));
  // 0218  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=218", u8"D"));
  // 0219  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=219", u8"E"));
}

// 0221  #start 19
TEST_F(HA762_OrOperator, Test_19)
{
  std::list<std::string> contexts;

  // 0222  CL
  arb_->clearArbitration();
  // 0223  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=223"));
  EXPECT_TRUE(isSatisfiedConstraints("line=223"));
  // 0224  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=224"));
  EXPECT_TRUE(isSatisfiedConstraints("line=224"));
  // 0225  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=225"));
  EXPECT_TRUE(isSatisfiedConstraints("line=225"));
  // 0226  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=226", u8"A"));
  // 0227  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=227", u8"B"));
  // 0228  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=228", u8"C"));
  // 0229  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=229", u8"D"));
  // 0230  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=230", u8"E"));
}

// 0232  #start 20
TEST_F(HA762_OrOperator, Test_20)
{
  std::list<std::string> contexts;

  // 0233  CL
  arb_->clearArbitration();
  // 0234  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=234"));
  EXPECT_TRUE(isSatisfiedConstraints("line=234"));
  // 0235  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=235"));
  EXPECT_TRUE(isSatisfiedConstraints("line=235"));
  // 0236  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=236"));
  EXPECT_TRUE(isSatisfiedConstraints("line=236"));
  // 0237  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=237", u8"A"));
  // 0238  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=238", u8"B"));
  // 0239  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=239", u8"C"));
  // 0240  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=240", u8"D"));
  // 0241  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=241", u8"E"));
}

// 0243  #start 21
TEST_F(HA762_OrOperator, Test_21)
{
  std::list<std::string> contexts;

  // 0244  CL
  arb_->clearArbitration();
  // 0245  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=245"));
  EXPECT_TRUE(isSatisfiedConstraints("line=245"));
  // 0246  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=246"));
  EXPECT_TRUE(isSatisfiedConstraints("line=246"));
  // 0247  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=247"));
  EXPECT_TRUE(isSatisfiedConstraints("line=247"));
  // 0248  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=248"));
  EXPECT_TRUE(isSatisfiedConstraints("line=248"));
  // 0249  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=249", u8"A"));
  // 0250  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=250", u8"B"));
  // 0251  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=251", u8"C"));
  // 0252  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=252", u8"D"));
  // 0253  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=253", u8"E"));
}

// 0255  #start 22
TEST_F(HA762_OrOperator, Test_22)
{
  std::list<std::string> contexts;

  // 0256  CL
  arb_->clearArbitration();
  // 0257  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=257"));
  EXPECT_TRUE(isSatisfiedConstraints("line=257"));
  // 0258  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=258"));
  EXPECT_TRUE(isSatisfiedConstraints("line=258"));
  // 0259  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=259"));
  EXPECT_TRUE(isSatisfiedConstraints("line=259"));
  // 0260  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=260"));
  EXPECT_TRUE(isSatisfiedConstraints("line=260"));
  // 0261  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=261", u8"A"));
  // 0262  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=262", u8"B"));
  // 0263  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=263", u8"C"));
  // 0264  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=264", u8"D"));
  // 0265  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=265", u8"E"));
}

// 0267  #start 23
TEST_F(HA762_OrOperator, Test_23)
{
  std::list<std::string> contexts;

  // 0268  CL
  arb_->clearArbitration();
  // 0269  C,on,a1,NORMAL
  result_ = arb_->execute(u8"a1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=269"));
  EXPECT_TRUE(isSatisfiedConstraints("line=269"));
  // 0270  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=270"));
  EXPECT_TRUE(isSatisfiedConstraints("line=270"));
  // 0271  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=271"));
  EXPECT_TRUE(isSatisfiedConstraints("line=271"));
  // 0272  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=272"));
  EXPECT_TRUE(isSatisfiedConstraints("line=272"));
  // 0273  Assert,A,A,a1
  EXPECT_EQ(u8"a1",getAllocated("line=273", u8"A"));
  // 0274  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=274", u8"B"));
  // 0275  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=275", u8"C"));
  // 0276  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=276", u8"D"));
  // 0277  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=277", u8"E"));
}

// 0279  #start 24
TEST_F(HA762_OrOperator, Test_24)
{
  std::list<std::string> contexts;

  // 0280  CL
  arb_->clearArbitration();
  // 0281  C,on,a2,NORMAL
  result_ = arb_->execute(u8"a2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=281"));
  EXPECT_TRUE(isSatisfiedConstraints("line=281"));
  // 0282  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=282"));
  EXPECT_TRUE(isSatisfiedConstraints("line=282"));
  // 0283  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=283"));
  EXPECT_TRUE(isSatisfiedConstraints("line=283"));
  // 0284  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=284"));
  EXPECT_TRUE(isSatisfiedConstraints("line=284"));
  // 0285  Assert,A,A,a2
  EXPECT_EQ(u8"a2",getAllocated("line=285", u8"A"));
  // 0286  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=286", u8"B"));
  // 0287  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=287", u8"C"));
  // 0288  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=288", u8"D"));
  // 0289  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=289", u8"E"));
}

// 0291  #start 25
TEST_F(HA762_OrOperator, Test_25)
{
  std::list<std::string> contexts;

  // 0292  CL
  arb_->clearArbitration();
  // 0293  C,on,b1,NORMAL
  result_ = arb_->execute(u8"b1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=293"));
  EXPECT_TRUE(isSatisfiedConstraints("line=293"));
  // 0294  C,on,c2,NORMAL
  result_ = arb_->execute(u8"c2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=294"));
  EXPECT_TRUE(isSatisfiedConstraints("line=294"));
  // 0295  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=295"));
  EXPECT_TRUE(isSatisfiedConstraints("line=295"));
  // 0296  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=296"));
  EXPECT_TRUE(isSatisfiedConstraints("line=296"));
  // 0297  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=297", u8"A"));
  // 0298  Assert,A,B,b1
  EXPECT_EQ(u8"b1",getAllocated("line=298", u8"B"));
  // 0299  Assert,A,C,c2
  EXPECT_EQ(u8"c2",getAllocated("line=299", u8"C"));
  // 0300  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=300", u8"D"));
  // 0301  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=301", u8"E"));
}

// 0303  #start 26
TEST_F(HA762_OrOperator, Test_26)
{
  std::list<std::string> contexts;

  // 0304  CL
  arb_->clearArbitration();
  // 0305  C,on,b2,NORMAL
  result_ = arb_->execute(u8"b2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=305"));
  EXPECT_TRUE(isSatisfiedConstraints("line=305"));
  // 0306  C,on,c1,NORMAL
  result_ = arb_->execute(u8"c1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=306"));
  EXPECT_TRUE(isSatisfiedConstraints("line=306"));
  // 0307  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=307"));
  EXPECT_TRUE(isSatisfiedConstraints("line=307"));
  // 0308  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=308"));
  EXPECT_TRUE(isSatisfiedConstraints("line=308"));
  // 0309  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=309", u8"A"));
  // 0310  Assert,A,B,b2
  EXPECT_EQ(u8"b2",getAllocated("line=310", u8"B"));
  // 0311  Assert,A,C,c1
  EXPECT_EQ(u8"c1",getAllocated("line=311", u8"C"));
  // 0312  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=312", u8"D"));
  // 0313  Assert,A,E,e1
  EXPECT_EQ(u8"e1",getAllocated("line=313", u8"E"));
}

// 0315  #start 27
TEST_F(HA762_OrOperator, Test_27)
{
  std::list<std::string> contexts;

  // 0316  CL
  arb_->clearArbitration();
  // 0317  C,on,d1,NORMAL
  result_ = arb_->execute(u8"d1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=317"));
  EXPECT_TRUE(isSatisfiedConstraints("line=317"));
  // 0318  C,on,e1,NORMAL
  result_ = arb_->execute(u8"e1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=318"));
  EXPECT_TRUE(isSatisfiedConstraints("line=318"));
  // 0319  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=319", u8"A"));
  // 0320  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=320", u8"B"));
  // 0321  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=321", u8"C"));
  // 0322  Assert,A,D,d1
  EXPECT_EQ(u8"d1",getAllocated("line=322", u8"D"));
  // 0323  Assert,A,E,
  EXPECT_EQ(u8"",getAllocated("line=323", u8"E"));
}

}

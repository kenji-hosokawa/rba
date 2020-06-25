// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1208_LetStatement_Multiple.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1208_LetStatement_Multiple.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1208_LetStatement_Multiple::HA1208_LetStatement_Multiple() {}
HA1208_LetStatement_Multiple::~HA1208_LetStatement_Multiple() {}

void HA1208_LetStatement_Multiple::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple.log",
                                                        LOGPATH"/HA1208_LetStatement_Multiple.log",
                                                        true);
  // カバレッジログの設定
  logm_ = std::make_unique<rba::RBALogManager>();
  logm_->addCoverageLogCollector(collector.get());
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_, logm_.get());
  for (auto constraint : model_->getConstraints()) {
    dynamic_cast<RBAConstraintImpl*>(constraint)->createHierarchy();
  }
  logm_->removeCoverageLogCollector(collector.get());
  // ログの設定
  RBALogManager::init(4);  // 全ログ出力
  RBALogManager::setEnable(RBALogManager::TYPE_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_PREVIOUS_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_ARBITRATE, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CANCEL_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_SAVE_LOG, true);
#else
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
#endif
}

void HA1208_LetStatement_Multiple::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1208_LetStatement_Multiple::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1208_LetStatement_Multiple::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1208_LetStatement_Multiple::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1208_LetStatement_Multiple::getAllocated(const std::string& msg,
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

bool HA1208_LetStatement_Multiple::isCanceled(const std::string& msg,
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

bool HA1208_LetStatement_Multiple::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1208_LetStatement_Multiple::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1208_LetStatement_Multiple::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1208_LetStatement_Multiple::isEnableContext(const std::string& msg,
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

bool HA1208_LetStatement_Multiple::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1208_LetStatement_Multiple::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1208_LetStatement_Multiple, Test_01)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple_Test_01.log",
                                                       LOGPATH"/HA1208_LetStatement_Multiple_Test_01.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"A"));
  // 0005  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"B"));
  // 0006  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"C"));
  // 0007  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=7", u8"D"));
  // 0008  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"X"));
  // 0009  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=9", u8"Y"));
  // 0010  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=10", u8"Z"));
  // 0011  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=11", u8"A1"));
  // 0012  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=12", u8"A2"));
  // 0013  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=13", u8"B1"));
  // 0014  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=14", u8"B2"));
  // 0015  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=15", u8"C2"));
  // 0016  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=16", u8"D1"));
  // 0017  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=17", u8"X1"));
  // 0018  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=19", u8"A"));
  // 0020  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=20", u8"B"));
  // 0021  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=21", u8"C"));
  // 0022  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=22", u8"D"));
  // 0023  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=23", u8"X"));
  // 0024  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=24", u8"Y"));
  // 0025  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"Z"));
  // 0026  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=26", u8"A1"));
  // 0027  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=27", u8"A2"));
  // 0028  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=28", u8"B1"));
  // 0029  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=29", u8"B2"));
  // 0030  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=30", u8"C2"));
  // 0031  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=31", u8"D1"));
  // 0032  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=32", u8"X1"));
  // 0033  C,on,B2,NORMAL
  result_ = arb_->execute(u8"B2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,B2
  EXPECT_EQ(u8"B2",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=36", u8"C"));
  // 0037  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=37", u8"D"));
  // 0038  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=38", u8"X"));
  // 0039  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=39", u8"Y"));
  // 0040  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=40", u8"Z"));
  // 0041  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=41", u8"A1"));
  // 0042  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=42", u8"A2"));
  // 0043  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=43", u8"B1"));
  // 0044  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=44", u8"B2"));
  // 0045  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=45", u8"C2"));
  // 0046  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=46", u8"D1"));
  // 0047  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=47", u8"X1"));
  // 0048  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=48"));
  EXPECT_TRUE(isSatisfiedConstraints("line=48"));
  // 0049  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=49", u8"A"));
  // 0050  Assert,A,B,B2
  EXPECT_EQ(u8"B2",getAllocated("line=50", u8"B"));
  // 0051  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=51", u8"C"));
  // 0052  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=52", u8"D"));
  // 0053  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=53", u8"X"));
  // 0054  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=54", u8"Y"));
  // 0055  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=55", u8"Z"));
  // 0056  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=56", u8"A1"));
  // 0057  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=57", u8"A2"));
  // 0058  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=58", u8"B1"));
  // 0059  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=59", u8"B2"));
  // 0060  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=60", u8"C2"));
  // 0061  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=61", u8"D1"));
  // 0062  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=62", u8"X1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0063  #start 2
TEST_F(HA1208_LetStatement_Multiple, Test_02)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple_Test_02.log",
                                                       LOGPATH"/HA1208_LetStatement_Multiple_Test_02.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0064  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0065  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=65"));
  EXPECT_TRUE(isSatisfiedConstraints("line=65"));
  // 0066  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=66", u8"A"));
  // 0067  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=67", u8"B"));
  // 0068  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=68", u8"C"));
  // 0069  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=69", u8"D"));
  // 0070  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=70", u8"X"));
  // 0071  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=71", u8"Y"));
  // 0072  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=72", u8"Z"));
  // 0073  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=73", u8"A1"));
  // 0074  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=74", u8"A2"));
  // 0075  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=75", u8"B1"));
  // 0076  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=76", u8"B2"));
  // 0077  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=77", u8"C2"));
  // 0078  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=78", u8"D1"));
  // 0079  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=79", u8"X1"));
  // 0080  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=80"));
  EXPECT_TRUE(isSatisfiedConstraints("line=80"));
  // 0081  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=81", u8"A"));
  // 0082  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=82", u8"B"));
  // 0083  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=83", u8"C"));
  // 0084  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=84", u8"D"));
  // 0085  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=85", u8"X"));
  // 0086  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=86", u8"Y"));
  // 0087  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=87", u8"Z"));
  // 0088  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=88", u8"A1"));
  // 0089  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=89", u8"A2"));
  // 0090  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=90", u8"B1"));
  // 0091  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=91", u8"B2"));
  // 0092  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=92", u8"C2"));
  // 0093  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=93", u8"D1"));
  // 0094  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=94", u8"X1"));
  // 0095  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=95"));
  EXPECT_TRUE(isSatisfiedConstraints("line=95"));
  // 0096  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=96", u8"A"));
  // 0097  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=97", u8"B"));
  // 0098  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=98", u8"C"));
  // 0099  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=99", u8"D"));
  // 0100  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=100", u8"X"));
  // 0101  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=101", u8"Y"));
  // 0102  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=102", u8"Z"));
  // 0103  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=103", u8"A1"));
  // 0104  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=104", u8"A2"));
  // 0105  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=105", u8"B1"));
  // 0106  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=106", u8"B2"));
  // 0107  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=107", u8"C2"));
  // 0108  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=108", u8"D1"));
  // 0109  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=109", u8"X1"));
  // 0110  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=110"));
  EXPECT_TRUE(isSatisfiedConstraints("line=110"));
  // 0111  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=111", u8"A"));
  // 0112  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=112", u8"B"));
  // 0113  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=113", u8"C"));
  // 0114  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=114", u8"D"));
  // 0115  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=115", u8"X"));
  // 0116  Assert,A,Y,X1
  EXPECT_EQ(u8"X1",getAllocated("line=116", u8"Y"));
  // 0117  Assert,A,Z,X1
  EXPECT_EQ(u8"X1",getAllocated("line=117", u8"Z"));
  // 0118  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=118", u8"A1"));
  // 0119  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=119", u8"A2"));
  // 0120  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=120", u8"B1"));
  // 0121  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=121", u8"B2"));
  // 0122  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=122", u8"C2"));
  // 0123  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=123", u8"D1"));
  // 0124  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=124", u8"X1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0125  #start 3
TEST_F(HA1208_LetStatement_Multiple, Test_03)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple_Test_03.log",
                                                       LOGPATH"/HA1208_LetStatement_Multiple_Test_03.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0126  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0127  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=127"));
  EXPECT_TRUE(isSatisfiedConstraints("line=127"));
  // 0128  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=128", u8"A"));
  // 0129  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=129", u8"B"));
  // 0130  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=130", u8"C"));
  // 0131  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=131", u8"D"));
  // 0132  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=132", u8"X"));
  // 0133  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=133", u8"Y"));
  // 0134  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=134", u8"Z"));
  // 0135  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=135", u8"A1"));
  // 0136  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=136", u8"A2"));
  // 0137  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=137", u8"B1"));
  // 0138  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=138", u8"B2"));
  // 0139  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=139", u8"C2"));
  // 0140  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=140", u8"D1"));
  // 0141  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=141", u8"X1"));
  // 0142  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=142"));
  EXPECT_TRUE(isSatisfiedConstraints("line=142"));
  // 0143  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=143", u8"A"));
  // 0144  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=144", u8"B"));
  // 0145  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=145", u8"C"));
  // 0146  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=146", u8"D"));
  // 0147  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=147", u8"X"));
  // 0148  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=148", u8"Y"));
  // 0149  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=149", u8"Z"));
  // 0150  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=150", u8"A1"));
  // 0151  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=151", u8"A2"));
  // 0152  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=152", u8"B1"));
  // 0153  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=153", u8"B2"));
  // 0154  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=154", u8"C2"));
  // 0155  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=155", u8"D1"));
  // 0156  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=156", u8"X1"));
  // 0157  C,on,C2,NORMAL
  result_ = arb_->execute(u8"C2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=157"));
  EXPECT_TRUE(isSatisfiedConstraints("line=157"));
  // 0158  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=158", u8"A"));
  // 0159  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=159", u8"B"));
  // 0160  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=160", u8"C"));
  // 0161  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=161", u8"D"));
  // 0162  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=162", u8"X"));
  // 0163  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=163", u8"Y"));
  // 0164  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=164", u8"Z"));
  // 0165  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=165", u8"A1"));
  // 0166  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=166", u8"A2"));
  // 0167  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=167", u8"B1"));
  // 0168  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=168", u8"B2"));
  // 0169  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=169", u8"C2"));
  // 0170  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=170", u8"D1"));
  // 0171  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=171", u8"X1"));
  // 0172  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=172"));
  EXPECT_TRUE(isSatisfiedConstraints("line=172"));
  // 0173  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=173", u8"A"));
  // 0174  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=174", u8"B"));
  // 0175  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=175", u8"C"));
  // 0176  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=176", u8"D"));
  // 0177  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=177", u8"X"));
  // 0178  Assert,A,Y,X1
  EXPECT_EQ(u8"X1",getAllocated("line=178", u8"Y"));
  // 0179  Assert,A,Z,X1
  EXPECT_EQ(u8"X1",getAllocated("line=179", u8"Z"));
  // 0180  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=180", u8"A1"));
  // 0181  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=181", u8"A2"));
  // 0182  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=182", u8"B1"));
  // 0183  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=183", u8"B2"));
  // 0184  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=184", u8"C2"));
  // 0185  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=185", u8"D1"));
  // 0186  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=186", u8"X1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0187  #start 4
TEST_F(HA1208_LetStatement_Multiple, Test_04)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple_Test_04.log",
                                                       LOGPATH"/HA1208_LetStatement_Multiple_Test_04.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0188  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0189  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=189"));
  EXPECT_TRUE(isSatisfiedConstraints("line=189"));
  // 0190  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=190", u8"A"));
  // 0191  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=191", u8"B"));
  // 0192  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=192", u8"C"));
  // 0193  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=193", u8"D"));
  // 0194  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=194", u8"X"));
  // 0195  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=195", u8"Y"));
  // 0196  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=196", u8"Z"));
  // 0197  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=197", u8"A1"));
  // 0198  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=198", u8"A2"));
  // 0199  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=199", u8"B1"));
  // 0200  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=200", u8"B2"));
  // 0201  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=201", u8"C2"));
  // 0202  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=202", u8"D1"));
  // 0203  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=203", u8"X1"));
  // 0204  C,on,A2,NORMAL
  result_ = arb_->execute(u8"A2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=204"));
  EXPECT_TRUE(isSatisfiedConstraints("line=204"));
  // 0205  Assert,A,A,A2
  EXPECT_EQ(u8"A2",getAllocated("line=205", u8"A"));
  // 0206  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=206", u8"B"));
  // 0207  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=207", u8"C"));
  // 0208  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=208", u8"D"));
  // 0209  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=209", u8"X"));
  // 0210  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=210", u8"Y"));
  // 0211  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=211", u8"Z"));
  // 0212  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=212", u8"A1"));
  // 0213  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=213", u8"A2"));
  // 0214  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=214", u8"B1"));
  // 0215  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=215", u8"B2"));
  // 0216  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=216", u8"C2"));
  // 0217  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=217", u8"D1"));
  // 0218  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=218", u8"X1"));
  // 0219  C,on,C2,NORMAL
  result_ = arb_->execute(u8"C2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=219"));
  EXPECT_TRUE(isSatisfiedConstraints("line=219"));
  // 0220  Assert,A,A,A2
  EXPECT_EQ(u8"A2",getAllocated("line=220", u8"A"));
  // 0221  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=221", u8"B"));
  // 0222  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=222", u8"C"));
  // 0223  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=223", u8"D"));
  // 0224  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=224", u8"X"));
  // 0225  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=225", u8"Y"));
  // 0226  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=226", u8"Z"));
  // 0227  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=227", u8"A1"));
  // 0228  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=228", u8"A2"));
  // 0229  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=229", u8"B1"));
  // 0230  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=230", u8"B2"));
  // 0231  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=231", u8"C2"));
  // 0232  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=232", u8"D1"));
  // 0233  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=233", u8"X1"));
  // 0234  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=234"));
  EXPECT_TRUE(isSatisfiedConstraints("line=234"));
  // 0235  Assert,A,A,A2
  EXPECT_EQ(u8"A2",getAllocated("line=235", u8"A"));
  // 0236  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=236", u8"B"));
  // 0237  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=237", u8"C"));
  // 0238  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=238", u8"D"));
  // 0239  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=239", u8"X"));
  // 0240  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=240", u8"Y"));
  // 0241  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=241", u8"Z"));
  // 0242  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=242", u8"A1"));
  // 0243  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=243", u8"A2"));
  // 0244  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=244", u8"B1"));
  // 0245  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=245", u8"B2"));
  // 0246  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=246", u8"C2"));
  // 0247  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=247", u8"D1"));
  // 0248  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=248", u8"X1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0249  #start 5
TEST_F(HA1208_LetStatement_Multiple, Test_05)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Multiple_Test_05.log",
                                                       LOGPATH"/HA1208_LetStatement_Multiple_Test_05.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0250  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0251  C,on,D1,NORMAL
  result_ = arb_->execute(u8"D1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=251"));
  EXPECT_TRUE(isSatisfiedConstraints("line=251"));
  // 0252  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=252", u8"A"));
  // 0253  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=253", u8"B"));
  // 0254  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=254", u8"C"));
  // 0255  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=255", u8"D"));
  // 0256  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=256", u8"X"));
  // 0257  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=257", u8"Y"));
  // 0258  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=258", u8"Z"));
  // 0259  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=259", u8"A1"));
  // 0260  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=260", u8"A2"));
  // 0261  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=261", u8"B1"));
  // 0262  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=262", u8"B2"));
  // 0263  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=263", u8"C2"));
  // 0264  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=264", u8"D1"));
  // 0265  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=265", u8"X1"));
  // 0266  C,on,C2,NORMAL
  result_ = arb_->execute(u8"C2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=266"));
  EXPECT_TRUE(isSatisfiedConstraints("line=266"));
  // 0267  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=267", u8"A"));
  // 0268  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=268", u8"B"));
  // 0269  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=269", u8"C"));
  // 0270  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=270", u8"D"));
  // 0271  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=271", u8"X"));
  // 0272  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=272", u8"Y"));
  // 0273  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=273", u8"Z"));
  // 0274  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=274", u8"A1"));
  // 0275  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=275", u8"A2"));
  // 0276  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=276", u8"B1"));
  // 0277  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=277", u8"B2"));
  // 0278  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=278", u8"C2"));
  // 0279  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=279", u8"D1"));
  // 0280  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=280", u8"X1"));
  // 0281  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=281"));
  EXPECT_TRUE(isSatisfiedConstraints("line=281"));
  // 0282  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=282", u8"A"));
  // 0283  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=283", u8"B"));
  // 0284  Assert,A,C,C2
  EXPECT_EQ(u8"C2",getAllocated("line=284", u8"C"));
  // 0285  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=285", u8"D"));
  // 0286  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=286", u8"X"));
  // 0287  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=287", u8"Y"));
  // 0288  Assert,A,Z,
  EXPECT_EQ(u8"",getAllocated("line=288", u8"Z"));
  // 0289  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=289", u8"A1"));
  // 0290  Assert,C,isCanceled,A2,false
  EXPECT_FALSE(isCanceled("line=290", u8"A2"));
  // 0291  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=291", u8"B1"));
  // 0292  Assert,C,isCanceled,B2,false
  EXPECT_FALSE(isCanceled("line=292", u8"B2"));
  // 0293  Assert,C,isCanceled,C2,false
  EXPECT_FALSE(isCanceled("line=293", u8"C2"));
  // 0294  Assert,C,isCanceled,D1,false
  EXPECT_FALSE(isCanceled("line=294", u8"D1"));
  // 0295  Assert,C,isCanceled,X1,false
  EXPECT_FALSE(isCanceled("line=295", u8"X1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

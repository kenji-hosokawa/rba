// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1208_LetStatement.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1208_LetStatement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1208_LetStatement::HA1208_LetStatement() {}
HA1208_LetStatement::~HA1208_LetStatement() {}

void HA1208_LetStatement::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement.log",
                                                        LOGPATH"/HA1208_LetStatement.log",
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

void HA1208_LetStatement::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1208_LetStatement::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1208_LetStatement::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1208_LetStatement::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1208_LetStatement::getAllocated(const std::string& msg,
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

bool HA1208_LetStatement::isCanceled(const std::string& msg,
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

bool HA1208_LetStatement::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1208_LetStatement::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1208_LetStatement::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1208_LetStatement::isEnableContext(const std::string& msg,
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

bool HA1208_LetStatement::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1208_LetStatement::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 A1.NORMAL,B1.NORMAL
TEST_F(HA1208_LetStatement, Test_01)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_01.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_01.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=4", u8"A"));
  // 0005  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"B"));
  // 0006  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"C"));
  // 0007  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=7", u8"A1"));
  // 0008  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=8", u8"B1"));
  // 0009  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=9", u8"C1"));
  // 0010  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=10"));
  EXPECT_TRUE(isSatisfiedConstraints("line=10"));
  // 0011  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=11", u8"A"));
  // 0012  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=12", u8"B"));
  // 0013  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"C"));
  // 0014  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=14", u8"A1"));
  // 0015  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=15", u8"B1"));
  // 0016  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=16", u8"C1"));
  // 0017  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=18", u8"A"));
  // 0019  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=19", u8"B"));
  // 0020  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=20", u8"C"));
  // 0021  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=21", u8"A1"));
  // 0022  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=22", u8"B1"));
  // 0023  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=23", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0024  #start 2 A1.NORMAL,C1.NORMAL
TEST_F(HA1208_LetStatement, Test_02)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_02.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_02.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0025  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0026  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=26"));
  EXPECT_TRUE(isSatisfiedConstraints("line=26"));
  // 0027  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=27", u8"A"));
  // 0028  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=28", u8"B"));
  // 0029  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=29", u8"C"));
  // 0030  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=30", u8"A1"));
  // 0031  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=31", u8"B1"));
  // 0032  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=32", u8"C1"));
  // 0033  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=36", u8"C"));
  // 0037  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=37", u8"A1"));
  // 0038  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=38", u8"B1"));
  // 0039  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=39", u8"C1"));
  // 0040  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=40"));
  EXPECT_TRUE(isSatisfiedConstraints("line=40"));
  // 0041  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=41", u8"A"));
  // 0042  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=42", u8"B"));
  // 0043  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=43", u8"C"));
  // 0044  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=44", u8"A1"));
  // 0045  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=45", u8"B1"));
  // 0046  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=46", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0047  #start 3 B1.NORMAL,A1.NORMAL
TEST_F(HA1208_LetStatement, Test_03)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_03.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_03.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0048  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0049  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=49"));
  EXPECT_TRUE(isSatisfiedConstraints("line=49"));
  // 0050  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=50", u8"A"));
  // 0051  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=51", u8"B"));
  // 0052  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=52", u8"C"));
  // 0053  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=53", u8"A1"));
  // 0054  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=54", u8"B1"));
  // 0055  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=55", u8"C1"));
  // 0056  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=56"));
  EXPECT_TRUE(isSatisfiedConstraints("line=56"));
  // 0057  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=57", u8"A"));
  // 0058  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=58", u8"B"));
  // 0059  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=59", u8"C"));
  // 0060  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=60", u8"A1"));
  // 0061  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=61", u8"B1"));
  // 0062  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=62", u8"C1"));
  // 0063  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=63"));
  EXPECT_TRUE(isSatisfiedConstraints("line=63"));
  // 0064  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=64", u8"A"));
  // 0065  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=65", u8"B"));
  // 0066  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=66", u8"C"));
  // 0067  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=67", u8"A1"));
  // 0068  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=68", u8"B1"));
  // 0069  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=69", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0070  #start 4 B1.NORMAL,C1.NORMAL
TEST_F(HA1208_LetStatement, Test_04)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_04.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_04.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0071  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0072  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=72"));
  EXPECT_TRUE(isSatisfiedConstraints("line=72"));
  // 0073  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=73", u8"A"));
  // 0074  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=74", u8"B"));
  // 0075  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=75", u8"C"));
  // 0076  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=76", u8"A1"));
  // 0077  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=77", u8"B1"));
  // 0078  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=78", u8"C1"));
  // 0079  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=79"));
  EXPECT_TRUE(isSatisfiedConstraints("line=79"));
  // 0080  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=80", u8"A"));
  // 0081  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=81", u8"B"));
  // 0082  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=82", u8"C"));
  // 0083  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=83", u8"A1"));
  // 0084  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=84", u8"B1"));
  // 0085  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=85", u8"C1"));
  // 0086  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=86"));
  EXPECT_TRUE(isSatisfiedConstraints("line=86"));
  // 0087  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=87", u8"A"));
  // 0088  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=88", u8"B"));
  // 0089  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=89", u8"C"));
  // 0090  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=90", u8"A1"));
  // 0091  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=91", u8"B1"));
  // 0092  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=92", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0093  #start 5 C1.NORMAL,A1.NORMAL
TEST_F(HA1208_LetStatement, Test_05)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_05.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_05.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0094  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0095  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=95"));
  EXPECT_TRUE(isSatisfiedConstraints("line=95"));
  // 0096  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=96", u8"A"));
  // 0097  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=97", u8"B"));
  // 0098  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=98", u8"C"));
  // 0099  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=99", u8"A1"));
  // 0100  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=100", u8"B1"));
  // 0101  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=101", u8"C1"));
  // 0102  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=102"));
  EXPECT_TRUE(isSatisfiedConstraints("line=102"));
  // 0103  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=103", u8"A"));
  // 0104  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=104", u8"B"));
  // 0105  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=105", u8"C"));
  // 0106  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=106", u8"A1"));
  // 0107  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=107", u8"B1"));
  // 0108  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=108", u8"C1"));
  // 0109  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=109"));
  EXPECT_TRUE(isSatisfiedConstraints("line=109"));
  // 0110  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=110", u8"A"));
  // 0111  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=111", u8"B"));
  // 0112  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=112", u8"C"));
  // 0113  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=113", u8"A1"));
  // 0114  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=114", u8"B1"));
  // 0115  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=115", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0116  #start 6 C1.NORMAL,B1.NORMAL
TEST_F(HA1208_LetStatement, Test_06)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_Test_06.log",
                                                       LOGPATH"/HA1208_LetStatement_Test_06.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0117  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0118  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=118"));
  EXPECT_TRUE(isSatisfiedConstraints("line=118"));
  // 0119  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=119", u8"A"));
  // 0120  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=120", u8"B"));
  // 0121  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=121", u8"C"));
  // 0122  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=122", u8"A1"));
  // 0123  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=123", u8"B1"));
  // 0124  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=124", u8"C1"));
  // 0125  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=125"));
  EXPECT_TRUE(isSatisfiedConstraints("line=125"));
  // 0126  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=126", u8"A"));
  // 0127  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=127", u8"B"));
  // 0128  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=128", u8"C"));
  // 0129  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=129", u8"A1"));
  // 0130  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=130", u8"B1"));
  // 0131  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=131", u8"C1"));
  // 0132  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=132"));
  EXPECT_TRUE(isSatisfiedConstraints("line=132"));
  // 0133  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=133", u8"A"));
  // 0134  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=134", u8"B"));
  // 0135  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=135", u8"C"));
  // 0136  Assert,C,isCanceled,A1,false
  EXPECT_FALSE(isCanceled("line=136", u8"A1"));
  // 0137  Assert,C,isCanceled,B1,false
  EXPECT_FALSE(isCanceled("line=137", u8"B1"));
  // 0138  Assert,C,isCanceled,C1,false
  EXPECT_FALSE(isCanceled("line=138", u8"C1"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1208_LetStatement_SameName.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1208_LetStatement_SameName.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1208_LetStatement_SameName::HA1208_LetStatement_SameName() {}
HA1208_LetStatement_SameName::~HA1208_LetStatement_SameName() {}

void HA1208_LetStatement_SameName::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_SameName.log",
                                                        LOGPATH"/HA1208_LetStatement_SameName.log",
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

void HA1208_LetStatement_SameName::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1208_LetStatement_SameName::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1208_LetStatement_SameName::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1208_LetStatement_SameName::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1208_LetStatement_SameName::getAllocated(const std::string& msg,
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

bool HA1208_LetStatement_SameName::isCanceled(const std::string& msg,
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

bool HA1208_LetStatement_SameName::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1208_LetStatement_SameName::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1208_LetStatement_SameName::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1208_LetStatement_SameName::isEnableContext(const std::string& msg,
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

bool HA1208_LetStatement_SameName::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1208_LetStatement_SameName::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1208_LetStatement_SameName, Test_01)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_SameName_Test_01.log",
                                                       LOGPATH"/HA1208_LetStatement_SameName_Test_01.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  C,on,F1,NORMAL
  result_ = arb_->execute(u8"F1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,A2,NORMAL
  result_ = arb_->execute(u8"A2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  C,on,E1,NORMAL
  result_ = arb_->execute(u8"E1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  // 0006  Assert,A,A,A2
  EXPECT_EQ(u8"A2",getAllocated("line=6", u8"A"));
  // 0007  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"B"));
  // 0008  Assert,A,C,A2
  EXPECT_EQ(u8"A2",getAllocated("line=8", u8"C"));
  // 0009  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=9", u8"D"));
  // 0010  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=10", u8"E"));
  // 0011  Assert,A,F,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"F"));
  // 0012  Assert,A,G,
  EXPECT_EQ(u8"",getAllocated("line=12", u8"G"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0014  #start 2
TEST_F(HA1208_LetStatement_SameName, Test_02)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_SameName_Test_02.log",
                                                       LOGPATH"/HA1208_LetStatement_SameName_Test_02.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0015  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0016  C,on,F1,NORMAL
  result_ = arb_->execute(u8"F1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=16"));
  EXPECT_TRUE(isSatisfiedConstraints("line=16"));
  // 0017  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,E1,NORMAL
  result_ = arb_->execute(u8"E1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=19", u8"A"));
  // 0020  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=20", u8"B"));
  // 0021  Assert,A,C,
  EXPECT_EQ(u8"",getAllocated("line=21", u8"C"));
  // 0022  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=22", u8"D"));
  // 0023  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=23", u8"E"));
  // 0024  Assert,A,F,F1
  EXPECT_EQ(u8"F1",getAllocated("line=24", u8"F"));
  // 0025  Assert,A,G,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"G"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0027  #start 3
TEST_F(HA1208_LetStatement_SameName, Test_03)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1208_LetStatement_SameName_Test_03.log",
                                                       LOGPATH"/HA1208_LetStatement_SameName_Test_03.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0028  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0029  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  C,on,A2,NORMAL
  result_ = arb_->execute(u8"A2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=30"));
  EXPECT_TRUE(isSatisfiedConstraints("line=30"));
  // 0031  C,on,E1,NORMAL
  result_ = arb_->execute(u8"E1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=31"));
  EXPECT_TRUE(isSatisfiedConstraints("line=31"));
  // 0032  C,on,F1,NORMAL
  result_ = arb_->execute(u8"F1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=32"));
  EXPECT_TRUE(isSatisfiedConstraints("line=32"));
  // 0033  C,on,G1,NORMAL
  result_ = arb_->execute(u8"G1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,A2
  EXPECT_EQ(u8"A2",getAllocated("line=36", u8"C"));
  // 0037  Assert,A,D,
  EXPECT_EQ(u8"",getAllocated("line=37", u8"D"));
  // 0038  Assert,A,E,E1
  EXPECT_EQ(u8"E1",getAllocated("line=38", u8"E"));
  // 0039  Assert,A,F,F1
  EXPECT_EQ(u8"F1",getAllocated("line=39", u8"F"));
  // 0040  Assert,A,G,G1
  EXPECT_EQ(u8"G1",getAllocated("line=40", u8"G"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

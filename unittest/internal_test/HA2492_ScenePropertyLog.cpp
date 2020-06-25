// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA2492_ScenePropertyLog.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA2492_ScenePropertyLog.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA2492_ScenePropertyLog::HA2492_ScenePropertyLog() {}
HA2492_ScenePropertyLog::~HA2492_ScenePropertyLog() {}

void HA2492_ScenePropertyLog::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2492_ScenePropertyLog.log",
                                                       LOGPATH"/HA2492_ScenePropertyLog.log",
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

void HA2492_ScenePropertyLog::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA2492_ScenePropertyLog::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA2492_ScenePropertyLog::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA2492_ScenePropertyLog::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA2492_ScenePropertyLog::getAllocated(const std::string& msg,
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

bool HA2492_ScenePropertyLog::isCanceled(const std::string& msg,
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

bool HA2492_ScenePropertyLog::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA2492_ScenePropertyLog::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA2492_ScenePropertyLog::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA2492_ScenePropertyLog::isEnableContext(const std::string& msg,
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

bool HA2492_ScenePropertyLog::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA2492_ScenePropertyLog::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 Default
TEST_F(HA2492_ScenePropertyLog, Test_01)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2492_ScenePropertyLog_Test_01.log",
                                                       LOGPATH"/HA2492_ScenePropertyLog_Test_01.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  S,off,s1
  result_ = arb_->execute(u8"s1", false);
  EXPECT_TRUE(isSuccess("line=3"));
  // 0004  S,off,s2
  result_ = arb_->execute(u8"s2", false);
  EXPECT_TRUE(isSuccess("line=4"));
  // 0005  S,off,s3
  result_ = arb_->execute(u8"s3", false);
  EXPECT_TRUE(isSuccess("line=5"));
  // 0006  S,off,s4
  result_ = arb_->execute(u8"s4", false);
  EXPECT_TRUE(isSuccess("line=6"));
  // 0007  Assert,S,s1,off
  EXPECT_FALSE(isActive("line=7", u8"s1"));
  // 0008  Assert,S,s2,off
  EXPECT_FALSE(isActive("line=8", u8"s2"));
  // 0009  Assert,S,s3,off,p31,31
  EXPECT_FALSE(isActive("line=9", u8"s3"));
  EXPECT_EQ(31, getProperty("line=9", u8"s3", u8"p31"));
  // 0010  Assert,S,s4,off,p41,41,p42,42
  EXPECT_FALSE(isActive("line=10", u8"s4"));
  EXPECT_EQ(41, getProperty("line=10", u8"s4", u8"p41"));
  EXPECT_FALSE(isActive("line=10", u8"s4"));
  EXPECT_EQ(42, getProperty("line=10", u8"s4", u8"p42"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0012  #start 2 Rule Not Apply
TEST_F(HA2492_ScenePropertyLog, Test_02)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2492_ScenePropertyLog_Test_02.log",
                                                       LOGPATH"/HA2492_ScenePropertyLog_Test_02.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0013  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0014  S,on,s1
  result_ = arb_->execute(u8"s1", true);
  EXPECT_TRUE(isSuccess("line=14"));
  // 0015  S,on,s2
  result_ = arb_->execute(u8"s2", true);
  EXPECT_TRUE(isSuccess("line=15"));
  // 0016  S,on,s3
  result_ = arb_->execute(u8"s3", true);
  EXPECT_TRUE(isSuccess("line=16"));
  // 0017  S,on,s4
  result_ = arb_->execute(u8"s4", true);
  EXPECT_TRUE(isSuccess("line=17"));
  // 0018  Assert,S,s1,on
  EXPECT_TRUE(isActive("line=18", u8"s1"));
  // 0019  Assert,S,s2,on
  EXPECT_TRUE(isActive("line=19", u8"s2"));
  // 0020  Assert,S,s3,on,p31,31
  EXPECT_TRUE(isActive("line=20", u8"s3"));
  EXPECT_EQ(31, getProperty("line=20", u8"s3", u8"p31"));
  // 0021  Assert,S,s4,on,p41,41,p42,42
  EXPECT_TRUE(isActive("line=21", u8"s4"));
  EXPECT_EQ(41, getProperty("line=21", u8"s4", u8"p41"));
  EXPECT_TRUE(isActive("line=21", u8"s4"));
  EXPECT_EQ(42, getProperty("line=21", u8"s4", u8"p42"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0040  #start 4 Property at Scene Off
TEST_F(HA2492_ScenePropertyLog, Test_04)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2492_ScenePropertyLog_Test_04.log",
                                                       LOGPATH"/HA2492_ScenePropertyLog_Test_04.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0041  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0042  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=42"));
  EXPECT_TRUE(isSatisfiedConstraints("line=42"));
  // 0043  S,off,s3,p31:111
  {
    std::list<std::pair<std::string, std::int32_t>> props;
    props.insert(props.begin(), {"p31",111});
    bool res = arb_->setScene(u8"s3", false, props);
    EXPECT_TRUE(isTrue("line=43", res));
    result_ = arb_->execute();
    EXPECT_TRUE(isSuccess("line=43"));
  }
  // 0044  Assert,S,s3,off,p31,111
  EXPECT_FALSE(isActive("line=44", u8"s3"));
  EXPECT_EQ(111, getProperty("line=44", u8"s3", u8"p31"));
  // 0045  Assert,A,A
  EXPECT_EQ(u8"",getAllocated("line=45", u8"A"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

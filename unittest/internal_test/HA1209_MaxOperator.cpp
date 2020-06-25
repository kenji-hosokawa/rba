// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_MaxOperator.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1209_MaxOperator.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1209_MaxOperator::HA1209_MaxOperator() {}
HA1209_MaxOperator::~HA1209_MaxOperator() {}

void HA1209_MaxOperator::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator.log",
                                                        LOGPATH"/HA1209_MaxOperator.log",
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

void HA1209_MaxOperator::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1209_MaxOperator::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1209_MaxOperator::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1209_MaxOperator::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1209_MaxOperator::getAllocated(const std::string& msg,
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

bool HA1209_MaxOperator::isCanceled(const std::string& msg,
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

bool HA1209_MaxOperator::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1209_MaxOperator::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1209_MaxOperator::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1209_MaxOperator::isEnableContext(const std::string& msg,
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

bool HA1209_MaxOperator::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1209_MaxOperator::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start Rhs_Allocatable
TEST_F(HA1209_MaxOperator, Rhs_Allocatable)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator_Rhs_Allocatable.log",
                                                       LOGPATH"/HA1209_MaxOperator_Rhs_Allocatable.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  C,on,S1
  result_ = arb_->execute(u8"S1", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"A"));
  // 0006  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=6"));
  EXPECT_TRUE(isSatisfiedConstraints("line=6"));
  // 0007  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"A"));
  // 0008  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=8", u8"B"));
  // 0009  C,on,B1,WARNING
  result_ = arb_->execute(u8"B1/WARNING", true);
  EXPECT_TRUE(isSuccess("line=9"));
  EXPECT_TRUE(isSatisfiedConstraints("line=9"));
  // 0010  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=10", u8"A"));
  // 0011  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"B"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0013  #start Lhs_Allocatable
TEST_F(HA1209_MaxOperator, Lhs_Allocatable)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator_Lhs_Allocatable.log",
                                                       LOGPATH"/HA1209_MaxOperator_Lhs_Allocatable.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0014  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0015  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"B"));
  // 0017  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=17", u8"X"));
  // 0018  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=19", u8"B"));
  // 0020  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=20", u8"X"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0022  #start Rhs_Content
TEST_F(HA1209_MaxOperator, Rhs_Content)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator_Rhs_Content.log",
                                                       LOGPATH"/HA1209_MaxOperator_Rhs_Content.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0023  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0024  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=24"));
  EXPECT_TRUE(isSatisfiedConstraints("line=24"));
  // 0025  C,on,S2
  result_ = arb_->execute(u8"S2", true);
  EXPECT_TRUE(isSuccess("line=25"));
  EXPECT_TRUE(isSatisfiedConstraints("line=25"));
  // 0026  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"A"));
  // 0027  C,off,S2
  result_ = arb_->execute(u8"S2", false);
  EXPECT_TRUE(isSuccess("line=27"));
  EXPECT_TRUE(isSatisfiedConstraints("line=27"));
  // 0028  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=28", u8"A"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0030  #start Lhs_Content
TEST_F(HA1209_MaxOperator, Lhs_Content)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator_Lhs_Content.log",
                                                       LOGPATH"/HA1209_MaxOperator_Lhs_Content.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0031  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0032  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=32"));
  EXPECT_TRUE(isSatisfiedConstraints("line=32"));
  // 0033  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"Y"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0037  #start NULL
TEST_F(HA1209_MaxOperator, NULL)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_MaxOperator_NULL.log",
                                                       LOGPATH"/HA1209_MaxOperator_NULL.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0038  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0039  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=39"));
  EXPECT_TRUE(isSatisfiedConstraints("line=39"));
  // 0040  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=40", u8"A"));
  // 0041  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=41", u8"Y"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_SizeOperator.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1209_SizeOperator.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1209_SizeOperator::HA1209_SizeOperator() {}
HA1209_SizeOperator::~HA1209_SizeOperator() {}

void HA1209_SizeOperator::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_SizeOperator.log",
                                                        LOGPATH"/HA1209_SizeOperator.log",
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

void HA1209_SizeOperator::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1209_SizeOperator::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1209_SizeOperator::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1209_SizeOperator::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1209_SizeOperator::getAllocated(const std::string& msg,
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

bool HA1209_SizeOperator::isCanceled(const std::string& msg,
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

bool HA1209_SizeOperator::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1209_SizeOperator::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1209_SizeOperator::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1209_SizeOperator::isEnableContext(const std::string& msg,
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

bool HA1209_SizeOperator::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1209_SizeOperator::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start ALL_and_SetOf
TEST_F(HA1209_SizeOperator, ALL_and_SetOf)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_SizeOperator_ALL_and_SetOf.log",
                                                       LOGPATH"/HA1209_SizeOperator_ALL_and_SetOf.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0002  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0003  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"X"));
  // 0005  Assert,A,XX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=5", u8"XX"));
  // 0006  Assert,A,XXX,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"XXX"));
  // 0007  Assert,A,XXXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=7", u8"XXXX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0009  #start select
TEST_F(HA1209_SizeOperator, select)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_SizeOperator_select.log",
                                                       LOGPATH"/HA1209_SizeOperator_select.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0010  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0011  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=12"));
  EXPECT_TRUE(isSatisfiedConstraints("line=12"));
  // 0013  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=13", u8"B"));
  // 0014  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"X"));
  // 0015  Assert,A,XX,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"XX"));
  // 0016  Assert,A,XXX,
  EXPECT_EQ(u8"",getAllocated("line=16", u8"XXX"));
  // 0017  Assert,A,XXXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=17", u8"XXXX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0019  #start allocatables
TEST_F(HA1209_SizeOperator, allocatables)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_SizeOperator_allocatables.log",
                                                       LOGPATH"/HA1209_SizeOperator_allocatables.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0020  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0021  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=21"));
  EXPECT_TRUE(isSatisfiedConstraints("line=21"));
  // 0022  C,on,A1,NORMAL
  result_ = arb_->execute(u8"A1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=22"));
  EXPECT_TRUE(isSatisfiedConstraints("line=22"));
  // 0023  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=23", u8"A"));
  // 0024  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=24", u8"X"));
  // 0025  Assert,A,XX,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"XX"));
  // 0026  Assert,A,XXX,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"XXX"));
  // 0027  Assert,A,XXXX,
  EXPECT_EQ(u8"",getAllocated("line=27", u8"XXXX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

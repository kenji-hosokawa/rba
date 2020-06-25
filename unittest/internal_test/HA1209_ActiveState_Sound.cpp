// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1209_ActiveState_Sound.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1209_ActiveState_Sound.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"

namespace {

using namespace rba;

void HA1209_ActiveState_Sound::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound.log",
                                                        LOGPATH"/HA1209_ActiveState_Sound.log",
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

void HA1209_ActiveState_Sound::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1209_ActiveState_Sound::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1209_ActiveState_Sound::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1209_ActiveState_Sound::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1209_ActiveState_Sound::getAllocated(const std::string& msg,
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

bool HA1209_ActiveState_Sound::isCanceled(const std::string& msg,
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

bool HA1209_ActiveState_Sound::isActive(const std::string& msg,
                                        const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1209_ActiveState_Sound::getProperty(const std::string& msg,
                                              const std::string& sceneName,
                                              const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1209_ActiveState_Sound::isEnableAllocatable(const std::string& msg,
                                                   const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1209_ActiveState_Sound::isEnableContext(const std::string& msg,
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

bool HA1209_ActiveState_Sound::isEnableScene(const std::string& msg,
                                             const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1209_ActiveState_Sound::isAttenuated(const std::string& msg,
                                            const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start false
TEST_F(HA1209_ActiveState_Sound, false)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound_false.log",
                                                       LOGPATH"/HA1209_ActiveState_Sound_false.log",
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
  // 0004  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=4", u8"X"));
  // 0005  Assert,A,XX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=5", u8"XX"));
  // 0006  Assert,A,XXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=6", u8"XXX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0008  #start true
TEST_F(HA1209_ActiveState_Sound, true)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound_true.log",
                                                       LOGPATH"/HA1209_ActiveState_Sound_true.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0009  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0010  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=10"));
  EXPECT_TRUE(isSatisfiedConstraints("line=10"));
  // 0011  C,on,A1,NORMAL1
  result_ = arb_->execute(u8"A1/NORMAL1", true);
  EXPECT_TRUE(isSuccess("line=11"));
  EXPECT_TRUE(isSatisfiedConstraints("line=11"));
  // 0012  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=12", u8"A"));
  // 0013  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"X"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0015  #start false_pre
TEST_F(HA1209_ActiveState_Sound, false_pre)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound_false_pre.log",
                                                       LOGPATH"/HA1209_ActiveState_Sound_false_pre.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0016  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0017  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,A1,NORMAL1
  result_ = arb_->execute(u8"A1/NORMAL1", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  C,on,A1,NORMAL2
  result_ = arb_->execute(u8"A1/NORMAL2", true);
  EXPECT_TRUE(isSuccess("line=19"));
  EXPECT_TRUE(isSatisfiedConstraints("line=19"));
  // 0020  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=20", u8"A"));
  // 0021  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=21", u8"X"));
  // 0022  Assert,A,XX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=22", u8"XX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0024  #start true_pre
TEST_F(HA1209_ActiveState_Sound, true_pre)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound_true_pre.log",
                                                       LOGPATH"/HA1209_ActiveState_Sound_true_pre.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0025  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0026  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=26"));
  EXPECT_TRUE(isSatisfiedConstraints("line=26"));
  // 0027  C,on,A1,NORMAL2
  result_ = arb_->execute(u8"A1/NORMAL2", true);
  EXPECT_TRUE(isSuccess("line=27"));
  EXPECT_TRUE(isSatisfiedConstraints("line=27"));
  // 0028  C,on,A1,NORMAL1
  result_ = arb_->execute(u8"A1/NORMAL1", true);
  EXPECT_TRUE(isSuccess("line=28"));
  EXPECT_TRUE(isSatisfiedConstraints("line=28"));
  // 0029  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=29", u8"A"));
  // 0030  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=30", u8"X"));
  // 0031  Assert,A,XX,
  EXPECT_EQ(u8"",getAllocated("line=31", u8"XX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0033  #start allocatedContent
TEST_F(HA1209_ActiveState_Sound, allocatedContent)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1209_ActiveState_Sound_allocatedContent.log",
                                                       LOGPATH"/HA1209_ActiveState_Sound_allocatedContent.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0034  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0035  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=35"));
  EXPECT_TRUE(isSatisfiedConstraints("line=35"));
  // 0036  C,on,A1,NORMAL3
  result_ = arb_->execute(u8"A1/NORMAL3", true);
  EXPECT_TRUE(isSuccess("line=36"));
  EXPECT_TRUE(isSatisfiedConstraints("line=36"));
  // 0037  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=37", u8"A"));
  // 0038  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=38", u8"X"));
  // 0039  Assert,A,XX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=39", u8"XX"));
  // 0040  Assert,A,XXX,
  EXPECT_EQ(u8"",getAllocated("line=40", u8"XXX"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

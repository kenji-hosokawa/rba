// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1210_IsTypeOfOperator.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1210_IsTypeOfOperator.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA1210_IsTypeOfOperator::HA1210_IsTypeOfOperator() {}
HA1210_IsTypeOfOperator::~HA1210_IsTypeOfOperator() {}

void HA1210_IsTypeOfOperator::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator.log",
                                                        LOGPATH"/HA1210_IsTypeOfOperator.log",
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

void HA1210_IsTypeOfOperator::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA1210_IsTypeOfOperator::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1210_IsTypeOfOperator::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1210_IsTypeOfOperator::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1210_IsTypeOfOperator::getAllocated(const std::string& msg,
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

bool HA1210_IsTypeOfOperator::isCanceled(const std::string& msg,
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

bool HA1210_IsTypeOfOperator::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1210_IsTypeOfOperator::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1210_IsTypeOfOperator::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1210_IsTypeOfOperator::isEnableContext(const std::string& msg,
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

bool HA1210_IsTypeOfOperator::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1210_IsTypeOfOperator::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start forViewContent
TEST_F(HA1210_IsTypeOfOperator, forViewContent)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator_forViewContent.log",
                                                       LOGPATH"/HA1210_IsTypeOfOperator_forViewContent.log",
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
  // 0004  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=4"));
  EXPECT_TRUE(isSatisfiedConstraints("line=4"));
  // 0005  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  // 0006  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=6", u8"A"));
  // 0007  Assert,A,X,X1
  EXPECT_EQ(u8"X1",getAllocated("line=7", u8"X"));
  // 0008  Assert,A,Y,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"Y"));
  // 0009  C,on,A2,NORMAL
  result_ = arb_->execute(u8"A2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=9"));
  EXPECT_TRUE(isSatisfiedConstraints("line=9"));
  // 0010  Assert,A,A,A2
  EXPECT_EQ(u8"A2",getAllocated("line=10", u8"A"));
  // 0011  Assert,A,X,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"X"));
  // 0012  Assert,A,Y,Y1
  EXPECT_EQ(u8"Y1",getAllocated("line=12", u8"Y"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0014  #start forSoundContent
TEST_F(HA1210_IsTypeOfOperator, forSoundContent)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator_forSoundContent.log",
                                                       LOGPATH"/HA1210_IsTypeOfOperator_forSoundContent.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0015  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0016  C,on,B1,NORMAL
  result_ = arb_->execute(u8"B1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=16"));
  EXPECT_TRUE(isSatisfiedConstraints("line=16"));
  // 0017  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=17"));
  EXPECT_TRUE(isSatisfiedConstraints("line=17"));
  // 0018  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=18"));
  EXPECT_TRUE(isSatisfiedConstraints("line=18"));
  // 0019  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=19", u8"B"));
  // 0020  Assert,A,XX,
  EXPECT_EQ(u8"",getAllocated("line=20", u8"XX"));
  // 0021  Assert,A,YY,Y1
  EXPECT_EQ(u8"Y1",getAllocated("line=21", u8"YY"));
  // 0022  C,on,B2,NORMAL
  result_ = arb_->execute(u8"B2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=22"));
  EXPECT_TRUE(isSatisfiedConstraints("line=22"));
  // 0023  Assert,A,B,B2
  EXPECT_EQ(u8"B2",getAllocated("line=23", u8"B"));
  // 0024  Assert,A,XX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=24", u8"XX"));
  // 0025  Assert,A,YY,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"YY"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0027  #start forArea
TEST_F(HA1210_IsTypeOfOperator, forArea)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator_forArea.log",
                                                       LOGPATH"/HA1210_IsTypeOfOperator_forArea.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0028  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0029  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=29"));
  EXPECT_TRUE(isSatisfiedConstraints("line=29"));
  // 0030  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=30"));
  EXPECT_TRUE(isSatisfiedConstraints("line=30"));
  // 0031  Assert,A,XXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=31", u8"XXX"));
  // 0032  Assert,A,YYY,
  EXPECT_EQ(u8"",getAllocated("line=32", u8"YYY"));
  // 0033  C,on,C1,NORMAL
  result_ = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=34", u8"C"));
  // 0035  Assert,A,XXX,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"XXX"));
  // 0036  Assert,A,YYY,Y1
  EXPECT_EQ(u8"Y1",getAllocated("line=36", u8"YYY"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0038  #start forZone
TEST_F(HA1210_IsTypeOfOperator, forZone)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator_forZone.log",
                                                       LOGPATH"/HA1210_IsTypeOfOperator_forZone.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0039  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0040  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=40"));
  EXPECT_TRUE(isSatisfiedConstraints("line=40"));
  // 0041  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=41"));
  EXPECT_TRUE(isSatisfiedConstraints("line=41"));
  // 0042  Assert,A,XXXX,
  EXPECT_EQ(u8"",getAllocated("line=42", u8"XXXX"));
  // 0043  Assert,A,YYYY,Y1
  EXPECT_EQ(u8"Y1",getAllocated("line=43", u8"YYYY"));
  // 0044  C,on,F1,NORMAL
  result_ = arb_->execute(u8"F1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=44"));
  EXPECT_TRUE(isSatisfiedConstraints("line=44"));
  // 0045  Assert,A,F,F1
  EXPECT_EQ(u8"F1",getAllocated("line=45", u8"F"));
  // 0046  Assert,A,XXXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=46", u8"XXXX"));
  // 0047  Assert,A,YYYY,
  EXPECT_EQ(u8"",getAllocated("line=47", u8"YYYY"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

// 0049  #start forMultiTag
TEST_F(HA1210_IsTypeOfOperator, forMultiTag)
{
  std::list<std::string> contexts;
#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA1210_IsTypeOfOperator_forMultiTag.log",
                                                       LOGPATH"/HA1210_IsTypeOfOperator_forMultiTag.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
  // 0050  CL
  arb_->clearArbitration();
#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
  // 0051  C,on,I1,NORMAL
  result_ = arb_->execute(u8"I1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=51"));
  EXPECT_TRUE(isSatisfiedConstraints("line=51"));
  // 0052  C,on,X1,NORMAL
  result_ = arb_->execute(u8"X1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=52"));
  EXPECT_TRUE(isSatisfiedConstraints("line=52"));
  // 0053  C,on,Y1,NORMAL
  result_ = arb_->execute(u8"Y1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=53"));
  EXPECT_TRUE(isSatisfiedConstraints("line=53"));
  // 0054  Assert,A,I,I1
  EXPECT_EQ(u8"I1",getAllocated("line=54", u8"I"));
  // 0055  Assert,A,XXXXX,X1
  EXPECT_EQ(u8"X1",getAllocated("line=55", u8"XXXXX"));
  // 0056  Assert,A,YYYYY,Y1
  EXPECT_EQ(u8"Y1",getAllocated("line=56", u8"YYYYY"));
  // 0057  C,on,I2,NORMAL
  result_ = arb_->execute(u8"I2/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=57"));
  EXPECT_TRUE(isSatisfiedConstraints("line=57"));
  // 0058  Assert,A,I,I2
  EXPECT_EQ(u8"I2",getAllocated("line=58", u8"I"));
  // 0059  Assert,A,XXXXX,
  EXPECT_EQ(u8"",getAllocated("line=59", u8"XXXXX"));
  // 0060  Assert,A,YYYYY,
  EXPECT_EQ(u8"",getAllocated("line=60", u8"YYYYY"));
#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
}

}

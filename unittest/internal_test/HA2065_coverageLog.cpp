// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA2065_coverageLog.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA2065_coverageLog.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"


namespace {

using namespace rba;

HA2065_coverageLog::HA2065_coverageLog() {}
HA2065_coverageLog::~HA2065_coverageLog() {}

void HA2065_coverageLog::SetUp()
{
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2065_coverageLog.log",
                                                       LOGPATH"/HA2065_coverageLog.log",
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
#else
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
#endif
}

void HA2065_coverageLog::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

bool HA2065_coverageLog::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA2065_coverageLog::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA2065_coverageLog::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA2065_coverageLog::getAllocated(const std::string& msg,
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

bool HA2065_coverageLog::isCanceled(const std::string& msg,
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

bool HA2065_coverageLog::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA2065_coverageLog::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA2065_coverageLog::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA2065_coverageLog::isEnableContext(const std::string& msg,
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

bool HA2065_coverageLog::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA2065_coverageLog::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

#ifdef RBA_USE_LOG
// 0001  #start 1 content1.NORMAL,content2.NORMAL
TEST_F(HA2065_coverageLog, Test_01)
{
  std::list<std::string> contexts;
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/HA2065_coverageLog_Test_01.log",
                                                       LOGPATH"/HA2065_coverageLog_Test_01.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
  // 0002  CL
  arb_->clearArbitration();
  RBALogManager::init(4);
  // 0003  C,on,content1,NORMAL
  result_ = arb_->execute(u8"content1/NORMAL", true);
  collector->log(result_->getLog());
  RBALogManager::init(4);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  C,on,content2,NORMAL,continue
  arb_->setContentState(u8"content2/NORMAL",true);
  // 0005  C,on,content3,NORMAL
  result_ = arb_->execute("content3/NORMAL", true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  collector->log(result_->getLog());
  logm_->removeCoverageLogCollector(collector.get());
}
#endif

}

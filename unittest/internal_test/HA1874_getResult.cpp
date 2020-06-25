// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1874_getResult.cpp
 */
#ifdef RBA_USE_LOG
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1874_getResult.hpp"

#include "RBAArbitrator.hpp"
#include "RBAViewAction.hpp"
#include "RBALogManager.hpp"

namespace {

using namespace rba;

HA1874_getResult::HA1874_getResult() {
}
HA1874_getResult::~HA1874_getResult() {
}

void HA1874_getResult::SetUp() {
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  logm_ = std::make_unique<RBALogManager>();
  arb_ = new RBAArbitrator(model_, logm_.get());
}

void HA1874_getResult::TearDown() {
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
  rba::RBALogManager::setLogManager(nullptr);
}

bool HA1874_getResult::isSuccess(const std::string &msg) {
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1874_getResult::isSatisfiedConstraints(const std::string &msg) {
  return result_->satisfiesConstraints();
}

bool HA1874_getResult::isTrue(const std::string &msg, bool res) {
  return res;
}

std::string HA1874_getResult::getAllocated(const std::string &msg,
                                           const std::string &allocName) {
  const RBAArea *area = model_->findArea(allocName);
  std::string contentName;
  if (area) {
    if (result_->isVisible(area)) {
      const RBAViewContentState *allocState = result_->getContentState(area);
      if (allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  } else {
    const RBAZone *zone = model_->findZone(allocName);
    if (result_->isSounding(zone)) {
      const RBASoundContentState *allocState = result_->getContentState(zone);
      if (allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  }
  return contentName;
}

bool HA1874_getResult::isCanceled(const std::string &msg,
                                  const std::string &contentName) {
  const RBAViewContent *viewContent = model_->findViewContent(contentName);
  if (viewContent) {
    // ビューの場合
    for (const RBAViewContentState *state : viewContent->getContentStates()) {
      if (result_->isCancel(state)) {
        return true;
      }
    }
  } else {
    // サウンドの場合
    const RBASoundContent *soundContent = model_->findSoundContent(contentName);
    for (const RBASoundContentState *state : soundContent->getContentStates()) {
      if (result_->isCancel(state)) {
        return true;
      }
    }
  }

  return false;
}

bool HA1874_getResult::isActive(const std::string &msg,
                                const std::string &sceneName) {
  const RBAScene *scene = model_->findScene(sceneName);
  if (scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1874_getResult::getProperty(const std::string &msg,
                                      const std::string &sceneName,
                                      const std::string &propertyName) {
  const RBAScene *scene = model_->findScene(sceneName);
  if (scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1874_getResult::isEnableAllocatable(const std::string &msg,
                                           const std::string &allocName) {
  const RBAArea *area = model_->findArea(allocName);
  if (area) {
    return true;
  }
  const RBAZone *zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1874_getResult::isEnableContext(const std::string &msg,
                                       const std::string &contextName) {
  // コンテントチェック
  std::string contentName = RBAViewContentState::getContentNameByContext(
      contextName);
  const RBAViewContent *viewContent = model_->findViewContent(contentName);
  if (viewContent) {
    std::string stateName = RBAViewContentState::getContentStateNameByContext(
        contextName);
    if (stateName.empty()) {
      return true;
    }
    const RBAViewContentState *state = model_->findViewContentState(
        contextName);
    return state != nullptr;
  } else {
    const RBASoundContent *soundContent = model_->findSoundContent(contentName);
    if (soundContent == nullptr) {
      return false;
    }
    std::string stateName = RBASoundContentState::getContentStateNameByContext(
        contextName);
    if (stateName.empty()) {
      return true;
    }
    const RBASoundContentState *state = model_->findSoundContentState(
        contextName);
    return state != nullptr;
  }
}

bool HA1874_getResult::isEnableScene(const std::string &msg,
                                     const std::string &sceneName) {
  const RBAScene *scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1874_getResult::isAttenuated(const std::string &msg,
                                    const std::string &zoneName) {
  const RBAZone *zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 A1.NORMAL,B1.NORMAL
TEST_F(HA1874_getResult, Test_01) {
  std::list<std::string> contexts;
  arb_->clearArbitration();
  RBALogManager::init(4);
  RBALogManager::setEnable(RBALogManager::TYPE_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_PREVIOUS_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_ARBITRATE, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CANCEL_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_SAVE_LOG, true);
  result_ = arb_->execute(u8"A1/NORMAL", true);
  // executeの戻り値のRBAResultを確認
  EXPECT_TRUE(isSuccess(""));
  EXPECT_TRUE(isSatisfiedConstraints(""));
  EXPECT_EQ(getAllocated("", "A"), "A1");
  std::string logTmp = result_->getLog();
  EXPECT_NE(logTmp, "");               // Logの確認
  ASSERT_EQ(result_->getViewActions().size(), 1U);  // ViewActionの確認
  EXPECT_EQ(result_->getViewActions().front()->getContent()->getName(), "A1");  // ViewActionの確認
  // getResultのRBAResultを確認
  RBAResult *targetResult = arb_->getResult();
  EXPECT_EQ(RBAResultStatusType::SUCCESS, targetResult->getStatusType());
  EXPECT_TRUE(targetResult->satisfiesConstraints());
  EXPECT_EQ(
      targetResult->getContentState(model_->findArea("A"))->getOwner()->getName(),
      "A1");
  EXPECT_EQ(targetResult->getLog(), logTmp);               // Logの確認
  ASSERT_EQ(targetResult->getViewActions().size(), 1U);  // ViewActionの確認
  EXPECT_EQ(targetResult->getViewActions().front()->getContent()->getName(),
            "A1");  // ViewActionの確認
}

}
#endif

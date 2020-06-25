// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 *HA412_Log_control.hpp
 */

#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include "RBAJsonParser.hpp"
#include "RBAModelImpl.hpp"
#include "HA412_Log_control.hpp"
#include "TestCommon.hpp"

namespace {

HA412_Log_control::HA412_Log_control(void)
{
}

HA412_Log_control::~HA412_Log_control(void)
{
}

#ifdef RBA_USE_LOG
void HA412_Log_control::SetUp(void)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
}

void HA412_Log_control::TearDown(void)
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
  if(logm_) {
    rba::RBALogManager::setLogManager(nullptr);
    delete logm_;
    logm_ = nullptr;
  }
}

TEST_F(HA412_Log_control, TYPE_REQUEST)
{
  logm_ = new rba::RBALogManager();
  rba::RBALogManager::setLogManager(logm_);
  rba::RBALogManager::init(4);  // 全ログ出力
  arb_ = new rba::RBAArbitrator(model_, logm_);

  // ログ設定: REQUEST ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_REQUEST, true);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_FALSE(rba::RBALogManager::getRequestLog().empty());  // ON
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());

  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: REQUEST OFF = ANY
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_REQUEST, false);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());
}

TEST_F(HA412_Log_control, TYPE_PREVIOUS_RESULT)
{
  logm_ = new rba::RBALogManager();
  rba::RBALogManager::setLogManager(logm_);
  rba::RBALogManager::init(4);  // 全ログ出力
  arb_ = new rba::RBAArbitrator(model_, logm_);

  // ログ設定: PREVIOUS_RESULT ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_PREVIOUS_RESULT,
				true);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_FALSE(rba::RBALogManager::getPreviousResultLog().empty());  // ON
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());

  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: PREVIOUS_RESULT OFF = ANY
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_PREVIOUS_RESULT,
				false);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());
}

TEST_F(HA412_Log_control, TYPE_ARBITRATE)
{
  logm_ = new rba::RBALogManager();
  rba::RBALogManager::setLogManager(logm_);
  rba::RBALogManager::init(4);  // 全ログ出力
  arb_ = new rba::RBAArbitrator(model_, logm_);

  // ログ設定: ARBITRATE ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_ARBITRATE, true);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_FALSE(rba::RBALogManager::getArbitrateLog().empty());  // ON
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());

  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: ARBITRATE OFF = ANY
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_ARBITRATE, false);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());
}

TEST_F(HA412_Log_control, TYPE_CANCEL_REQUEST)
{
  logm_ = new rba::RBALogManager();
  rba::RBALogManager::setLogManager(logm_);
  rba::RBALogManager::init(4);  // 全ログ出力
  arb_ = new rba::RBAArbitrator(model_, logm_);

  // ログ設定: CANCEL_REQUEST ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CANCEL_REQUEST, true);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_FALSE(rba::RBALogManager::getCancelRequestLog().empty());  // ON

  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: CANCEL_REQUEST OFF = ANY
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CANCEL_REQUEST, false);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());
}

TEST_F(HA412_Log_control, TYPE_CHECK_ALL_CONSTRAINTS)
{
  logm_ = new rba::RBALogManager();
  rba::RBALogManager::setLogManager(logm_);
  rba::RBALogManager::init(4);  // 全ログ出力
  arb_ = new rba::RBAArbitrator(model_, logm_);

  // ログ設定: CHECK_ALL_CONSTRAINTS ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS,
				true);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_FALSE(rba::RBALogManager::getCheckAllConstraintLog().empty());  // ON
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());

  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: CHECK_ALL_CONSTRAINTS OFF = ANY
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS,
				false);

  // 実行
  {
    std::list<std::string> contexts;
    contexts.push_back(u8"スピードメーター/NORMAL");
    std::unique_ptr<rba::RBAResult> result = arb_->execute(contexts, true);
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  // ログ出力チェック
  EXPECT_TRUE(rba::RBALogManager::getArbitrateLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCheckAllConstraintLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getRequestLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getPreviousResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getResultLog().empty());
  EXPECT_TRUE(rba::RBALogManager::getCancelRequestLog().empty());
}

#endif
}

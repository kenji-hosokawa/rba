// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1009_clear.cpp
 */

#include <list>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA1009_clear.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA1009_clear::HA1009_clear()
{
}

HA1009_clear::~HA1009_clear()
{
}

void HA1009_clear::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1009_clear::TearDown()
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
}

TEST_F(HA1009_clear, view)
{
  // get state
  const RBAViewContentState* vcontAnormal
    = model_->findViewContentState(u8"VContentA/NORMAL");
  ASSERT_NE(nullptr, vcontAnormal);
  const RBAViewContentState* vcontAint
    = model_->findViewContentState(u8"VContentA/INT");
  ASSERT_NE(nullptr, vcontAint);
  const RBAViewContentState* vcontBnormal
    = model_->findViewContentState(u8"VContentB/NORMAL");
  ASSERT_NE(nullptr, vcontBnormal);
  const RBAViewContentState* vcontCnormal
    = model_->findViewContentState(u8"VContentC/NORMAL");
  ASSERT_NE(nullptr, vcontCnormal);
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(3, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(3, vcontAint->getOrder());
  EXPECT_EQ(1, vcontBnormal->getOrder());
  EXPECT_EQ(2, vcontCnormal->getOrder());

  // Clear
  arb_->clearArbitration();
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  
  // 実行
  result_ = arb_->execute(u8"VContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(1, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(1, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(3, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(1, vcontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(3, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(1, vcontCnormal->getOrder());

  // 実行(OFF)
  result_ = arb_->execute(u8"VContentC/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(2, vcontAint->getOrder());
  EXPECT_EQ(1, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行(OFF)
  result_ = arb_->execute(u8"VContentB/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(1, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行(OFF) 
  result_ = arb_->execute(u8"VContentA/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // 実行(OFF) 
  result_ = arb_->execute(u8"VContentA/INT", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
}

TEST_F(HA1009_clear, view_init)
{
  // get state
  const RBAViewContentState* vcontAnormal
    = model_->findViewContentState(u8"VContentA/NORMAL");
  ASSERT_NE(nullptr, vcontAnormal);
  const RBAViewContentState* vcontAint
    = model_->findViewContentState(u8"VContentA/INT");
  ASSERT_NE(nullptr, vcontAint);
  const RBAViewContentState* vcontBnormal
    = model_->findViewContentState(u8"VContentB/NORMAL");
  ASSERT_NE(nullptr, vcontBnormal);
  const RBAViewContentState* vcontCnormal
    = model_->findViewContentState(u8"VContentC/NORMAL");
  ASSERT_NE(nullptr, vcontCnormal);
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());

  // Clear
  arb_->clearArbitration();
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  
  // 初期化
  std::list<std::string> contexts;
  contexts.push_back(u8"VContentA/NORMAL");
  contexts.push_back(u8"VContentB/NORMAL");
  arb_->initialize(contexts);

  // 実行
  result_ = arb_->execute();
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
}

TEST_F(HA1009_clear, sound)
{
  // get state
  const RBASoundContentState* scontAnormal
    = model_->findSoundContentState(u8"SContentA/NORMAL");
  ASSERT_NE(nullptr, scontAnormal);
  const RBASoundContentState* scontAint
    = model_->findSoundContentState(u8"SContentA/INT");
  ASSERT_NE(nullptr, scontAint);
  const RBASoundContentState* scontBnormal
    = model_->findSoundContentState(u8"SContentB/NORMAL");
  ASSERT_NE(nullptr, scontBnormal);
  const RBASoundContentState* scontCnormal
    = model_->findSoundContentState(u8"SContentC/NORMAL");
  ASSERT_NE(nullptr, scontCnormal);
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(3, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(3, scontAint->getOrder());
  EXPECT_EQ(1, scontBnormal->getOrder());
  EXPECT_EQ(2, scontCnormal->getOrder());

  // Clear
  arb_->clearArbitration();
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());
  
  // 実行
  result_ = arb_->execute(u8"SContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(1, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(1, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(3, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(1, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(3, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(1, scontCnormal->getOrder());

  // 実行(OFF)
  result_ = arb_->execute(u8"SContentC/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(2, scontAint->getOrder());
  EXPECT_EQ(1, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行(OFF)
  result_ = arb_->execute(u8"SContentB/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(1, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行(OFF) 
  result_ = arb_->execute(u8"SContentA/NORMAL", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行(OFF) 
  result_ = arb_->execute(u8"SContentA/INT", false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());
}

TEST_F(HA1009_clear, sound_init)
{
  // get state
  const RBASoundContentState* scontAnormal
    = model_->findSoundContentState(u8"SContentA/NORMAL");
  ASSERT_NE(nullptr, scontAnormal);
  const RBASoundContentState* scontAint
    = model_->findSoundContentState(u8"SContentA/INT");
  ASSERT_NE(nullptr, scontAint);
  const RBASoundContentState* scontBnormal
    = model_->findSoundContentState(u8"SContentB/NORMAL");
  ASSERT_NE(nullptr, scontBnormal);
  const RBASoundContentState* scontCnormal
    = model_->findSoundContentState(u8"SContentC/NORMAL");
  ASSERT_NE(nullptr, scontCnormal);
  // check order
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 初期化
  std::list<std::string> contexts;
  contexts.push_back(u8"SContentA/NORMAL");
  contexts.push_back(u8"SContentB/NORMAL");
  arb_->initialize(contexts);
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(contexts);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());
}

TEST_F(HA1009_clear, view_sound)
{
  // get state
  const RBAViewContentState* vcontAnormal
    = model_->findViewContentState(u8"VContentA/NORMAL");
  ASSERT_NE(nullptr, vcontAnormal);
  const RBAViewContentState* vcontAint
    = model_->findViewContentState(u8"VContentA/INT");
  ASSERT_NE(nullptr, vcontAint);
  const RBAViewContentState* vcontBnormal
    = model_->findViewContentState(u8"VContentB/NORMAL");
  ASSERT_NE(nullptr, vcontBnormal);
  const RBAViewContentState* vcontCnormal
    = model_->findViewContentState(u8"VContentC/NORMAL");
  ASSERT_NE(nullptr, vcontCnormal);
  const RBASoundContentState* scontAnormal
    = model_->findSoundContentState(u8"SContentA/NORMAL");
  ASSERT_NE(nullptr, scontAnormal);
  const RBASoundContentState* scontAint
    = model_->findSoundContentState(u8"SContentA/INT");
  ASSERT_NE(nullptr, scontAint);
  const RBASoundContentState* scontBnormal
    = model_->findSoundContentState(u8"SContentB/NORMAL");
  ASSERT_NE(nullptr, scontBnormal);
  const RBASoundContentState* scontCnormal
    = model_->findSoundContentState(u8"SContentC/NORMAL");
  ASSERT_NE(nullptr, scontCnormal);
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentB/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(3, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentC/NORMAL", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(1, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(2, vcontBnormal->getOrder());
  EXPECT_EQ(3, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(3, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"VContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(3, vcontAint->getOrder());
  EXPECT_EQ(1, vcontBnormal->getOrder());
  EXPECT_EQ(2, vcontCnormal->getOrder());
  EXPECT_EQ(1, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(2, scontBnormal->getOrder());
  EXPECT_EQ(3, scontCnormal->getOrder());

  // 実行
  result_ = arb_->execute(u8"SContentA/INT", true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS, result_->getStatusType());
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(3, vcontAint->getOrder());
  EXPECT_EQ(1, vcontBnormal->getOrder());
  EXPECT_EQ(2, vcontCnormal->getOrder());
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(3, scontAint->getOrder());
  EXPECT_EQ(1, scontBnormal->getOrder());
  EXPECT_EQ(2, scontCnormal->getOrder());

  // Clear
  arb_->clearArbitration();
  // check order
  EXPECT_EQ(0, vcontAnormal->getOrder());
  EXPECT_EQ(0, vcontAint->getOrder());
  EXPECT_EQ(0, vcontBnormal->getOrder());
  EXPECT_EQ(0, vcontCnormal->getOrder());
  EXPECT_EQ(0, scontAnormal->getOrder());
  EXPECT_EQ(0, scontAint->getOrder());
  EXPECT_EQ(0, scontBnormal->getOrder());
  EXPECT_EQ(0, scontCnormal->getOrder());

}

}

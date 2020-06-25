// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA792_getFailedConstraints.cpp
 */

#ifdef RBA_USE_LOG
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "RBALogManager.hpp"
#include "RBAResultImpl.hpp"
#include "HA792_getFailedConstraints.hpp"
#include "TestCommon.hpp"
#include "RBAConstraint.hpp"

namespace {

using namespace rba;

HA792_getFailedConstraints::HA792_getFailedConstraints()
{
}

HA792_getFailedConstraints::~HA792_getFailedConstraints()
{
}

void HA792_getFailedConstraints::SetUp()
{
}

void HA792_getFailedConstraints::TearDown()
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
  rba::RBALogManager::setLogManager(nullptr);
}

TEST_F(HA792_getFailedConstraints, mode_normal)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);

  std::unique_ptr<RBAResult> result;
  rba::RBAResultImpl* resultImpl;

  // 実行
  result = arb->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_TRUE(constraints.empty());
  }

  // 期待値比較
  // エリアA -> コンテンツA2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  // エリアC -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints = resultImpl->getFailedConstraints();
    EXPECT_EQ(0u, constraints.size());
  }

  // 実行
  result = arb->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_TRUE(constraints.empty());
  }

  // 期待値比較
  // エリアA -> コンテンツA2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> コンテンツB2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツB2", content->getName());
  }

  // 期待値比較
  // エリアC -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_EQ(0u, constraints.size());
  }

  // 実行
  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_TRUE(constraints.empty());
  }

  // 期待値比較
  // エリアA -> コンテンツA2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> コンテンツB2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツB2", content->getName());
  }

  // 期待値比較
  // エリアC -> コンテンツC2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツC2", content->getName());
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_EQ(0u, constraints.size());
  }
}

TEST_F(HA792_getFailedConstraints, mode_simulation)
{
  rba::RBALogManager logm;
  rba::RBALogManager::setLogManager(&logm);
  rba::RBALogManager::init(4);                  // 全ログ出力
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_ALL_CONSTRAINTS,true);

  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model, &logm);

  std::unique_ptr<RBAResult> result;
  rba::RBAResultImpl* resultImpl;

  // 実行
  result = arb->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_FALSE(constraints.empty()); // Exception
  }

  // 期待値比較
  // エリアA -> コンテンツA2/NORMAL
  // exception
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  // エリアC -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_EQ(1u, constraints.size());
    EXPECT_STREQ(u8"AndOperator", constraints.front()->getName().c_str());
  }

  // 実行
  result = arb->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_FALSE(constraints.empty()); // Exception
  }

  // 期待値比較
  // エリアA -> コンテンツA2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> コンテンツB2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツB2", content->getName());
  }

  // 期待値比較
  // エリアC -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_EQ(1u, constraints.size());
    EXPECT_STREQ(u8"AndOperator", constraints.front()->getName().c_str());
  }

  // 実行
  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  resultImpl = dynamic_cast<rba::RBAResultImpl*>(result.get());
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_TRUE(constraints.empty());
  }

  // 期待値比較
  // エリアA -> コンテンツA2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツA2", content->getName());
  }

  // 期待値比較
  // エリアB -> コンテンツB2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアB");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツB2", content->getName());
  }

  // 期待値比較
  // エリアC -> コンテンツC2
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアC");
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_EQ(u8"コンテンツC2", content->getName());
  }

  // 期待値比較
  {
    const std::list<const RBAConstraint*> constraints
      = resultImpl->getFailedConstraints();
    EXPECT_EQ(0u, constraints.size());
  }
}

}
#endif

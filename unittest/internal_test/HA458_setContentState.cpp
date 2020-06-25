// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA458_setContentState.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA458_setContentState.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA458_setContentState::HA458_setContentState(void)
{
}

HA458_setContentState::~HA458_setContentState(void)
{
}

void HA458_setContentState::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA458_setContentState::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA458_setContentState, setAllocatableResult_success)
{
  std::unique_ptr<RBAResult> result;

  // 実行
  result = arb->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  // 期待値比較
  // エリアA -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
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

  // 実行
  bool res = arb->setAllocatableResult(u8"エリアB", u8"コンテンツB2/NORMAL");
  EXPECT_TRUE(res);

  // 実行
  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

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
}

TEST_F(HA458_setContentState, setAllocatableResult_error)
{
  std::unique_ptr<RBAResult> result;

  // 実行
  result = arb->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  // 期待値比較
  // エリアA -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
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

  // エリア指定でエラー
  bool res = arb->setAllocatableResult(u8"エリアBB", u8"コンテンツB2/NORMAL");
  EXPECT_FALSE(res);

  // コンテンツ指定でエラー
  res = arb->setAllocatableResult(u8"エリアB", u8"コンテンツBB2/NORMAL");
  EXPECT_FALSE(res);

  // コンテンツステート指定でエラー
  res = arb->setAllocatableResult(u8"エリアB", u8"コンテンツB2/NORMALL");
  EXPECT_FALSE(res);

  // エリア指定とコンテキスト指定でエラー
  res = arb->setAllocatableResult(u8"エリアBB", u8"コンテンツB2/NORMALB");
  EXPECT_FALSE(res);

}

TEST_F(HA458_setContentState, clearArbitrator)
{
  std::unique_ptr<RBAResult> result;

  // 実行
  result = arb->execute(u8"コンテンツA2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  // 実行
  result = arb->execute(u8"コンテンツB2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  // 実行
  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

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

  // リセット
  arb->clearArbitration();

  // 実行
  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  // 期待値比較
  // エリアA -> -
  {
    const rba::RBAArea* area = arb->getModel()->findArea(u8"エリアA");
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
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
}

TEST_F(HA458_setContentState, setContentState)
{
  std::unique_ptr<RBAResult> result;

  {
    bool res = arb->setContentState(u8"コンテンツA2/NORMAL", true);
    EXPECT_TRUE(res);
  }

  {
    bool res = arb->setContentState(u8"コンテンツB2/NORMAL", true);
    EXPECT_TRUE(res);
  }

  result = arb->execute(u8"コンテンツC2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

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
}

TEST_F(HA458_setContentState, setScene)
{
  std::unique_ptr<RBAResult> result;
  std::int32_t val;
  const RBAScene* scene = model->findScene(u8"Global");

  // 初期値を確認
  {
    result = arb->execute();
    val = result->getSceneProperty(scene,"PropertyA");
    EXPECT_EQ(3, val);
  }

  // プロパティのA,Bをセット
  {
    std::list<std::pair<std::string, std::int32_t>> prop;
    prop.push_back(std::make_pair("PropertyA", 1000));
    prop.push_back(std::make_pair("PropertyB", -128)); //プロパティB(undefined)
    bool res = arb->setScene("Global", true, prop);
    EXPECT_TRUE(res);
  }

  // プロパティのA取得
  {
    result = arb->execute();
    val = result->getSceneProperty(scene,"PropertyA");
    EXPECT_EQ(1000, val);
  }
}

}

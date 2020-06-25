// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Scene_CallAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Scene_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Scene_CallAPI::HA497_Scene_CallAPI(void)
{
}

HA497_Scene_CallAPI::~HA497_Scene_CallAPI(void)
{
}

void HA497_Scene_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Scene_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_Scene_CallAPI, isGlobal) {
  const RBAScene* s1 = model->findScene(u8"S1");
  ASSERT_NE(nullptr, s1);
  EXPECT_FALSE(s1->isGlobal());
  const RBAScene* s2 = model->findScene(u8"S2");
  ASSERT_NE(nullptr, s2);
  EXPECT_TRUE(s2->isGlobal());
}
TEST_F(HA497_Scene_CallAPI, getPropertyValue) {
  const RBAScene* s1 = model->findScene(u8"S1");
  ASSERT_NE(nullptr, s1);
  const RBAScene* s2 = model->findScene(u8"S2");
  ASSERT_NE(nullptr, s2);
  const RBAScene* s3 = model->findScene(u8"S3");
  ASSERT_NE(nullptr, s3);
  // off状態のシーンに対する要求
  // ローカルシーン
  EXPECT_EQ(s1->getPropertyValue(u8""),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P1"),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P2"),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P3"),-1);
  // グローバルシーン
  EXPECT_EQ(s2->getPropertyValue(u8""),-1);
  EXPECT_EQ(s2->getPropertyValue(u8"P1"),10);
  EXPECT_EQ(s2->getPropertyValue(u8"P2"),0);
  EXPECT_EQ(s2->getPropertyValue(u8"P3"),-10);
  // グローバルシーン プロパティ名が他シーンと重複していた場合の確認
  EXPECT_EQ(s3->getPropertyValue(u8""),-1);
  EXPECT_EQ(s3->getPropertyValue(u8"P1"),100);
  EXPECT_EQ(s3->getPropertyValue(u8"P2"),0);
  EXPECT_EQ(s3->getPropertyValue(u8"P3"),-100);
  // デフォルト値を返す確認
  arb->execute(u8"A1");
  EXPECT_EQ(s2->getPropertyValue(u8"P1"),10);

  // on状態のシーンに対する要求
  arb->execute(u8"S1");
  arb->execute(u8"S2");
  arb->execute(u8"S3");
  // ローカルシーン
  ASSERT_NE(nullptr, s1);
  EXPECT_EQ(s1->getPropertyValue(u8""),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P1"),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P2"),-1);
  EXPECT_EQ(s1->getPropertyValue(u8"P3"),-1);
  // グローバルシーン
  ASSERT_NE(nullptr, s2);
  EXPECT_EQ(s2->getPropertyValue(u8""),-1);
  EXPECT_EQ(s2->getPropertyValue(u8"P1"),10);
  EXPECT_EQ(s2->getPropertyValue(u8"P2"),0);
  EXPECT_EQ(s2->getPropertyValue(u8"P3"),-10);
  // グローバルシーン プロパティ名が他シーンと重複していた場合の確認
  ASSERT_NE(nullptr, s3);
  EXPECT_EQ(s3->getPropertyValue(u8""),-1);
  EXPECT_EQ(s3->getPropertyValue(u8"P1"),100);
  EXPECT_EQ(s3->getPropertyValue(u8"P2"),0);
  EXPECT_EQ(s3->getPropertyValue(u8"P3"),-100);
  // デフォルト値を返す確認
  arb->execute(u8"B1");
  EXPECT_EQ(s3->getPropertyValue(u8"P3"),-100);
}
}

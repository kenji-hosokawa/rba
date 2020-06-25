// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_SoundContentState_CallAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_SoundContentState_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_SoundContentState_CallAPI::HA497_SoundContentState_CallAPI(void)
{
}

HA497_SoundContentState_CallAPI::~HA497_SoundContentState_CallAPI(void)
{
}

void HA497_SoundContentState_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_SoundContentState_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_SoundContentState_CallAPI, getPriority) {
  std::int32_t priority;
  priority = model->findSoundContentState(u8"A1/StateA1")->getPriority();
  EXPECT_EQ(11,priority);
  priority = model->findSoundContentState(u8"A1/StateA2")->getPriority();
  EXPECT_EQ(10,priority);
  priority = model->findSoundContentState(u8"B1/StateB1")->getPriority();
  EXPECT_EQ(21,priority);
  priority = model->findSoundContentState(u8"B1/StateB2")->getPriority();
  EXPECT_EQ(20,priority);
  priority = model->findSoundContentState(u8"C1/StateC1")->getPriority();
  EXPECT_EQ(30,priority);
  priority = model->findSoundContentState(u8"C1/StateC2")->getPriority();
  EXPECT_EQ(31,priority);
  priority = model->findSoundContentState(u8"D1/StateD1")->getPriority();
  EXPECT_EQ(41,priority);
  priority = model->findSoundContentState(u8"D1/StateD2")->getPriority();
  EXPECT_EQ(40,priority);
}
TEST_F(HA497_SoundContentState_CallAPI, getOrder) {
  std::int32_t orderA1;
  std::int32_t orderA2;
  std::int32_t orderB1;
  std::int32_t orderB2;
  std::int32_t orderC1;
  std::int32_t orderC2;
  std::int32_t orderV1;
  // 非アクティブな音声コンテント状態のオーダー値は0であることの確認
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(0,orderA1);
  EXPECT_EQ(0,orderA2);
  EXPECT_EQ(0,orderB1);
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(0,orderV1);
  // オーダー値は1から開始されることの確認
  arb->execute(u8"A1/StateA1");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(1,orderA1);
  EXPECT_EQ(0,orderA2);
  EXPECT_EQ(0,orderB1);
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(0,orderV1);
  // インクリメントされる整数値であることの確認
  arb->execute(u8"B1/StateB1");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(1,orderA1);
  EXPECT_EQ(0,orderA2);
  EXPECT_EQ(2,orderB1);
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(0,orderV1);
  // 既にアクティブなステート
  arb->execute(u8"B1/StateB1");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(1,orderA1);
  EXPECT_EQ(0,orderA2);
  EXPECT_LT(orderA1,orderB1); // orderA1 < orderB1
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(0,orderV1);
  // 同一コンテント別ステートの確認
  arb->execute(u8"A1/StateA2");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(0,orderA1);
  EXPECT_EQ(orderB1 + 1,orderA2);
  EXPECT_LT(0,orderB1); // 0 < orderB1
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(0,orderV1);
  // 表示コンテント状態に影響を受けないことの確認
  arb->execute(u8"ViewA1/NORMAL");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(0,orderA1);
  EXPECT_EQ(orderB1 + 1,orderA2);
  EXPECT_LT(0,orderB1); // 0 < orderB1
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(0,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(1,orderV1);
  arb->execute(u8"C1/StateC1");
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(0,orderA1);
  EXPECT_EQ(orderB1 + 1,orderA2);
  EXPECT_LT(0,orderB1); // 0 < orderB1
  EXPECT_EQ(0,orderB2);
  EXPECT_EQ(orderA2 + 1,orderC1);
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(1,orderV1);
  // 既にアクティブから非アクティブにしたときのステート
  arb->execute(u8"A1/StateA2",false);
  orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
  orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
  orderB1 = model->findSoundContentState(u8"B1/StateB1")->getOrder();
  orderB2 = model->findSoundContentState(u8"B1/StateB2")->getOrder();
  orderC1 = model->findSoundContentState(u8"C1/StateC1")->getOrder();
  orderC2 = model->findSoundContentState(u8"C1/StateC2")->getOrder();
  orderV1 = model->findViewContentState(u8"ViewA1/NORMAL")->getOrder();
  EXPECT_EQ(0,orderA1);
  EXPECT_EQ(0,orderA2);
  EXPECT_LT(0,orderB1); // 0 < orderB1
  EXPECT_EQ(0,orderB2);
  EXPECT_LT(orderB1,orderC1); //orderB1 < orderC1
  EXPECT_EQ(0,orderC2);
  EXPECT_EQ(1,orderV1);
  // オーバーフロー確認
#if 0 // 時間が掛かり過ぎるので除外
  for (std::int64_t i; i < 0x40000000;++i) {
    arb->execute(u8"A1/StateA1");
    arb->execute(u8"A1/StateA2");
    orderA1 = model->findSoundContentState(u8"A1/StateA1")->getOrder();
    orderA2 = model->findSoundContentState(u8"A1/StateA2")->getOrder();
    EXPECT_LT(orderA1,orderA2); // orderA1 < orderA2
  }
  for (std::int64_t i; i < 0x40000000;++i) {
    arb->execute(u8"A1/StateA1",false);
    arb->execute(u8"A1/StateA1");
    arb->execute(u8"A1/StateA2",false);
    arb->execute(u8"A1/StateA2");
    EXPECT_LT(orderA1,orderA2); // orderA1 < orderA2
  }
#endif
}
TEST_F(HA497_SoundContentState_CallAPI, getOwner) {
  const RBASoundContent* o = model->findSoundContentState(u8"A1/StateA1")->getOwner();
  EXPECT_EQ(model->findSoundContent(u8"A1"),o);
  o = model->findSoundContentState(u8"D1/StateD2")->getOwner();
  EXPECT_EQ(model->findSoundContent(u8"D1"),o);
}
TEST_F(HA497_SoundContentState_CallAPI, getContentNameByContext) {
  const RBASoundContentState* c = model->findSoundContentState(u8"A1/StateA1");
  std::string cName;
  ASSERT_NE(nullptr, c);
  cName = c->getContentNameByContext(u8"A1/StateA1");
  EXPECT_EQ(u8"A1",cName);
  cName = c->getContentNameByContext(u8"B1/StateB2");
  EXPECT_EQ(u8"B1",cName);
  cName = c->getContentNameByContext(u8"A1");
  EXPECT_EQ(u8"A1",cName);
  cName = c->getContentNameByContext(u8"StateA1");
  EXPECT_EQ(u8"StateA1",cName);
  cName = c->getContentNameByContext(u8"");
  EXPECT_EQ(u8"",cName);
}
TEST_F(HA497_SoundContentState_CallAPI, getContentStateNameByContext) {
  const RBASoundContentState* c = model->findSoundContentState(u8"A1/StateA1");
  std::string cName;
  ASSERT_NE(nullptr, c);
  cName = c->getContentStateNameByContext(u8"A1/StateA1");
  EXPECT_EQ(u8"StateA1",cName);
  cName = c->getContentStateNameByContext(u8"B1/StateB2");
  EXPECT_EQ(u8"StateB2",cName);
  cName = c->getContentStateNameByContext(u8"A1");
  EXPECT_EQ(u8"",cName);
  cName = c->getContentStateNameByContext(u8"StateA1");
  EXPECT_EQ(u8"",cName);
  cName = c->getContentStateNameByContext(u8"");
  EXPECT_EQ(u8"",cName);
}
}

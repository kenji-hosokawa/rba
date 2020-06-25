// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_Arbitrator_CallAPI.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_Arbitrator_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_Arbitrator_CallAPI::HA497_Arbitrator_CallAPI(void)
{
}

HA497_Arbitrator_CallAPI::~HA497_Arbitrator_CallAPI(void)
{
}

void HA497_Arbitrator_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_Arbitrator_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}
TEST_F(HA497_Arbitrator_CallAPI, execute_false) {
  std::unique_ptr<RBAResult> result;
  // 存在しないコンテキストを含む
  result = arb->execute(u8"Dummy");
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  std::list<std::string> contexts{u8"A1",u8"A2",u8"B1",u8"Dummy"};
  result = arb->execute(contexts);
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  result = arb->execute(u8"Dummy",true);
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  result = arb->execute(contexts,true);
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  result = arb->execute(u8"Dummy",false);
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  result = arb->execute(contexts,false);
  EXPECT_EQ(RBAResultStatusType::UNKNOWN_CONTENT_STATE,result->getStatusType());
  result = arb->execute();
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result->getStatusType());
}

TEST_F(HA497_Arbitrator_CallAPI, setScene_true) {
  std::unique_ptr<RBAResult> result;
  std::list<std::string> contexts{u8"A1",u8"A2",u8"B1",u8"B2",u8"C1",u8"C2",u8"C3",u8"D1",u8"D2",u8"D3",u8"E1",u8"E2",u8"E3"};
  result = arb->execute(contexts);
  const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
  const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
  const RBAViewContentState* CContent = result->getViewContentState(model->findArea(u8"C"));
  const RBAViewContentState* DContent = result->getViewContentState(model->findArea(u8"D"));
  const RBAViewContentState* EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  bool isPassed;
  std::list<std::pair<std::string, std::int32_t>> properties;
  // TRUE
  // ローカルシーン
  isPassed = arb->setScene(u8"S_local", true, properties);
  EXPECT_TRUE(isPassed);
  { // 調停処理は実行しない確認
    const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
    const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
    const RBAViewContentState* CContent = result->getViewContentState(model->findArea(u8"C"));
    const RBAViewContentState* DContent = result->getViewContentState(model->findArea(u8"D"));
    const RBAViewContentState* EContent = result->getViewContentState(model->findArea(u8"E"));
    EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
    EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
    EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
    EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
    EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  }
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // グローバルシーン、プロパティ変更なし
  isPassed = arb->setScene(u8"S_global", true, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // グローバルシーン、プロパティ変更あり
  properties.push_back(std::make_pair(u8"P1", 2));
  isPassed = arb->setScene(u8"S_global", true, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // グローバルシーン、複数プロパティ変更あり
  properties.push_back(std::make_pair(u8"P2", 20));
  properties.push_back(std::make_pair(u8"P3", 200));
  isPassed = arb->setScene(u8"S_global", true, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));
  // ローカルシーン 存在しないプロパティ
  isPassed = arb->setScene(u8"S_local", true, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));
  // グローバルシーン 存在しないプロパティ
  properties.push_back(std::make_pair(u8"Dummy", 2));
  isPassed = arb->setScene(u8"S_local", true, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));

  // FALSE
  // ローカルシーン
  isPassed = arb->setScene(u8"S_local", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));
  // グローバルシーン、プロパティ変更なし
  isPassed = arb->setScene(u8"S_global", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C2"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));
  // グローバルシーン、プロパティ変更あり
  properties.push_back(std::make_pair(u8"P1", 3));
  isPassed = arb->setScene(u8"S_global", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C1"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D2"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E2"));
  // グローバルシーン、複数プロパティ変更あり
  properties.push_back(std::make_pair(u8"P2", 30));
  properties.push_back(std::make_pair(u8"P3", 300));
  isPassed = arb->setScene(u8"S_global", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C1"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D1"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E1"));
  // ローカルシーン 存在しないプロパティ
  isPassed = arb->setScene(u8"S_local", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C1"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D1"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E1"));
  // グローバルシーン 存在しないプロパティ
  properties.push_back(std::make_pair(u8"Dummy", 2));
  isPassed = arb->setScene("S_global", false, properties);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C1"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D1"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E1"));
}
TEST_F(HA497_Arbitrator_CallAPI, setScene_false) {
  std::unique_ptr<RBAResult> result;
  std::list<std::string> contexts{u8"A1",u8"A2",u8"B1",u8"B2",u8"C1",u8"C2",u8"C3",u8"D1",u8"D2",u8"D3",u8"E1",u8"E2",u8"E3"};
  result = arb->execute(contexts);
  bool isPassed;
  std::list<std::pair<std::string, std::int32_t>> properties;
  // 存在しないシーン
  isPassed = arb->setScene(u8"Dummy", true, properties);
  EXPECT_FALSE(isPassed);
  result = arb->execute();
  const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
  const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
  const RBAViewContentState* CContent = result->getViewContentState(model->findArea(u8"C"));
  const RBAViewContentState* DContent = result->getViewContentState(model->findArea(u8"D"));
  const RBAViewContentState* EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
}
TEST_F(HA497_Arbitrator_CallAPI, setContentState_Scene) {
  std::unique_ptr<RBAResult> result;
  std::list<std::string> contexts{u8"A1",u8"A2",u8"B1",u8"B2",u8"C1",u8"C2",u8"C3",u8"D1",u8"D2",u8"D3",u8"E1",u8"E2",u8"E3"};
  result = arb->execute(contexts);
  const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
  const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
  const RBAViewContentState* CContent = result->getViewContentState(model->findArea(u8"C"));
  const RBAViewContentState* DContent = result->getViewContentState(model->findArea(u8"D"));
  const RBAViewContentState* EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  bool isPassed;
  // ローカルシーン true
  isPassed = arb->setContentState(u8"S_local", true);
  EXPECT_TRUE(isPassed);
  { // 調停処理は実行しない確認
    const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
    const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
    EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
    EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  }
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // グローバルシーン true
  isPassed = arb->setContentState(u8"S_global", true);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // ローカルシーン false
  isPassed = arb->setContentState(u8"S_local", false);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
  // グローバルシーン false
  isPassed = arb->setContentState(u8"S_global", false);
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
#if 0 // HA-893対応完了までコメントアウト。暫定対応
  // ローカルシーン require省略時
  isPassed = arb->setContentState(u8"S_local");
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
  // グローバルシーン require省略時
  isPassed = arb->setContentState(u8"S_global");
  EXPECT_TRUE(isPassed);
  result = arb->execute();
  AContent = result->getViewContentState(model->findArea(u8"A"));
  BContent = result->getViewContentState(model->findArea(u8"B"));
  CContent = result->getViewContentState(model->findArea(u8"C"));
  DContent = result->getViewContentState(model->findArea(u8"D"));
  EContent = result->getViewContentState(model->findArea(u8"E"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A2"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B2"));
  EXPECT_EQ(CContent,model->findViewContentState(u8"C3"));
  EXPECT_EQ(DContent,model->findViewContentState(u8"D3"));
  EXPECT_EQ(EContent,model->findViewContentState(u8"E3"));
#endif
}
TEST_F(HA497_Arbitrator_CallAPI, setContentState_false) {
  std::unique_ptr<RBAResult> result;
  std::list<std::string> contexts{u8"A1",u8"A2",u8"B1",u8"B2"};
  result = arb->execute(contexts);
  bool isPassed;
  // 存在しないシーン
  isPassed = arb->setContentState(u8"Dummy",true);
  EXPECT_FALSE(isPassed);
  result = arb->execute();
  const RBAViewContentState* AContent = result->getViewContentState(model->findArea(u8"A"));
  const RBAViewContentState* BContent = result->getViewContentState(model->findArea(u8"B"));
  EXPECT_EQ(AContent,model->findViewContentState(u8"A1"));
  EXPECT_EQ(BContent,model->findViewContentState(u8"B1"));
}
}

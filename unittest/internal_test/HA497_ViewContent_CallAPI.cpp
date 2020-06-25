// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA497_ViewContent_CallAPI.hpp
 */

#include <algorithm>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA497_ViewContent_CallAPI.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA497_ViewContent_CallAPI::HA497_ViewContent_CallAPI(void)
{
}

HA497_ViewContent_CallAPI::~HA497_ViewContent_CallAPI(void)
{
}

void HA497_ViewContent_CallAPI::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA497_ViewContent_CallAPI::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA497_ViewContent_CallAPI, getContentStates) {
  std::unique_ptr<RBAResult> result;
  const RBAViewContent* a1 = model->findViewContent(u8"A1");
  const RBAViewContent* b1 = model->findViewContent(u8"B1");
  const RBAViewContent* c1 = model->findViewContent(u8"C1");
  const RBAViewContent* d1 = model->findViewContent(u8"D1");
  ASSERT_NE(nullptr, a1);
  ASSERT_NE(nullptr, b1);
  ASSERT_NE(nullptr, c1);
  ASSERT_NE(nullptr, d1);
  const std::list<const RBAViewContentState*> a1List = a1->getContentStates();
  const std::list<const RBAViewContentState*> b1List = b1->getContentStates();
  const std::list<const RBAViewContentState*> c1List = c1->getContentStates();
  const std::list<const RBAViewContentState*> d1List = d1->getContentStates();
  ASSERT_EQ(a1List.size(), 2U);
  ASSERT_EQ(b1List.size(), 2U);
  ASSERT_EQ(c1List.size(), 2U);
  ASSERT_EQ(d1List.size(), 2U);
  EXPECT_NE(std::find(a1List.begin(),a1List.end(),model->findViewContentState(u8"A1/StateA1")),a1List.end());
  EXPECT_NE(std::find(a1List.begin(),a1List.end(),model->findViewContentState(u8"A1/StateA2")),a1List.end());
  EXPECT_NE(std::find(b1List.begin(),b1List.end(),model->findViewContentState(u8"B1/StateB1")),b1List.end());
  EXPECT_NE(std::find(b1List.begin(),b1List.end(),model->findViewContentState(u8"B1/StateB2")),b1List.end());
  EXPECT_NE(std::find(c1List.begin(),c1List.end(),model->findViewContentState(u8"C1/StateC1")),c1List.end());
  EXPECT_NE(std::find(c1List.begin(),c1List.end(),model->findViewContentState(u8"C1/StateC2")),c1List.end());
  EXPECT_NE(std::find(d1List.begin(),d1List.end(),model->findViewContentState(u8"D1/StateD1")),d1List.end());
  EXPECT_NE(std::find(d1List.begin(),d1List.end(),model->findViewContentState(u8"D1/StateD2")),d1List.end());
}

TEST_F(HA497_ViewContent_CallAPI, getAreas) {
  std::unique_ptr<RBAResult> result;
  const RBAViewContent* a1 = model->findViewContent(u8"A1");
  const RBAViewContent* b1 = model->findViewContent(u8"B1");
  const RBAViewContent* c1 = model->findViewContent(u8"C1");
  const RBAViewContent* d1 = model->findViewContent(u8"D1");
  ASSERT_NE(nullptr, a1);
  ASSERT_NE(nullptr, b1);
  ASSERT_NE(nullptr, c1);
  ASSERT_NE(nullptr, d1);
  const std::list<const RBAArea*> a1List = a1->getAreas();
  const std::list<const RBAArea*> b1List = b1->getAreas();
  const std::list<const RBAArea*> c1List = c1->getAreas();
  const std::list<const RBAArea*> d1List = d1->getAreas();
  ASSERT_EQ(a1List.size(), 1U);
  ASSERT_EQ(b1List.size(), 2U);
  ASSERT_EQ(c1List.size(), 1U);
  ASSERT_EQ(d1List.size(), 1U);
  EXPECT_NE(std::find(a1List.begin(),a1List.end(),model->findArea(u8"A")),a1List.end());
  EXPECT_NE(std::find(b1List.begin(),b1List.end(),model->findArea(u8"B")),b1List.end());
  EXPECT_NE(std::find(b1List.begin(),b1List.end(),model->findArea(u8"BB")),b1List.end());
  EXPECT_NE(std::find(c1List.begin(),c1List.end(),model->findArea(u8"C")),c1List.end());
  EXPECT_NE(std::find(d1List.begin(),d1List.end(),model->findArea(u8"D")),d1List.end());
}
TEST_F(HA497_ViewContent_CallAPI, getLoserType) {
  std::unique_ptr<RBAResult> result;
  const RBAViewContent* a1 = model->findViewContent(u8"A1");
  const RBAViewContent* b1 = model->findViewContent(u8"B1");
  const RBAViewContent* c1 = model->findViewContent(u8"C1");
  const RBAViewContent* d1 = model->findViewContent(u8"D1");
  ASSERT_NE(nullptr, a1);
  ASSERT_NE(nullptr, b1);
  ASSERT_NE(nullptr, c1);
  ASSERT_NE(nullptr, d1);
  RBAContentLoserType aType = a1->getLoserType();
  RBAContentLoserType bType = b1->getLoserType();
  RBAContentLoserType cType = c1->getLoserType();
  RBAContentLoserType dType = d1->getLoserType();
  EXPECT_EQ(aType,RBAContentLoserType::NEVER_GIVEUP);
  EXPECT_EQ(bType,RBAContentLoserType::GOOD_LOSER);
  EXPECT_EQ(cType,RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN);
  EXPECT_EQ(dType,RBAContentLoserType::NEVER_GIVEUP);

  //RBAContentLoserTypeの動作確認
  // rbaモデルで定義しない場合
  const RBAViewContent* sa1 = model->findViewContent(u8"A1");
  const RBAViewContent* sa2 = model->findViewContent(u8"A2");
  result = arb->execute();
  EXPECT_EQ(result->isActive(sa1),false);
  EXPECT_EQ(result->isActive(sa2),false);
  std::list<std::string> la{u8"A1/StateA2",u8"A2/NORMAL"};
  result = arb->execute(la);
  EXPECT_EQ(result->isActive(sa1),true);
  EXPECT_EQ(result->isActive(sa2),true);
  result = arb->execute();
  EXPECT_EQ(result->isActive(sa1),true);
  EXPECT_EQ(result->isActive(sa2),true);
  result = arb->execute("A2/NORMAL",false);
  EXPECT_EQ(result->isActive(sa1),true);
  EXPECT_EQ(result->isActive(sa2),false);
  result = arb->execute("A2/NORMAL",true);
  EXPECT_EQ(result->isActive(sa1),true);
  EXPECT_EQ(result->isActive(sa2),true);
  // GOOD_LOSER
  const RBAViewContent* sb1 = model->findViewContent(u8"B1"); // GOOD_LOSER
  const RBAViewContent* sb2 = model->findViewContent(u8"B2");
  result = arb->execute();
  EXPECT_EQ(result->isActive(sb1),false);
  EXPECT_EQ(result->isActive(sb2),false);
  std::list<std::string> lb{u8"B1/StateB2",u8"B2/NORMAL"};
  result = arb->execute(lb);
  EXPECT_EQ(result->isActive(sb1),false);
  EXPECT_EQ(result->isActive(sb2),true);
  result = arb->execute();
  EXPECT_EQ(result->isActive(sb1),false);
  EXPECT_EQ(result->isActive(sb2),true);
  result = arb->execute("B2/NORMAL",false);
  EXPECT_EQ(result->isActive(sb1),false);
  EXPECT_EQ(result->isActive(sb2),false);
  result = arb->execute("B2/NORMAL",true);
  EXPECT_EQ(result->isActive(sb1),false);
  EXPECT_EQ(result->isActive(sb2),true);
  // DO_NOT_GIVEUP_UNTIL_WIN
  const RBAViewContent* sc1 = model->findViewContent(u8"C1");
  const RBAViewContent* sc2 = model->findViewContent(u8"C2");
  result = arb->execute();
  EXPECT_EQ(result->isActive(sc1),false);
  EXPECT_EQ(result->isActive(sc2),false);
  std::list<std::string> lc{u8"C1/StateC2",u8"C2/NORMAL"};
  result = arb->execute(lc);
  EXPECT_EQ(result->isActive(sc1),true);
  EXPECT_EQ(result->isActive(sc2),true);
  result = arb->execute();
  EXPECT_EQ(result->isActive(sc1),true);
  EXPECT_EQ(result->isActive(sc2),true);
  result = arb->execute("C2/NORMAL",false);
  EXPECT_EQ(result->isActive(sc1),true);
  EXPECT_EQ(result->isActive(sc2),false);
  result = arb->execute("C2/NORMAL",true);
  EXPECT_EQ(result->isActive(sc1),false);
  EXPECT_EQ(result->isActive(sc2),true);
  // NEVER_GIVEUP
  const RBAViewContent* sd1 = model->findViewContent(u8"D1");
  const RBAViewContent* sd2 = model->findViewContent(u8"D2");
  result = arb->execute();
  EXPECT_EQ(result->isActive(sd1),false);
  EXPECT_EQ(result->isActive(sd2),false);
  std::list<std::string> ld{u8"D1/StateD2",u8"D2/NORMAL"};
  result = arb->execute(ld);
  EXPECT_EQ(result->isActive(sd1),true);
  EXPECT_EQ(result->isActive(sd2),true);
  result = arb->execute();
  EXPECT_EQ(result->isActive(sd1),true);
  EXPECT_EQ(result->isActive(sd2),true);
  result = arb->execute("D2/NORMAL",false);
  EXPECT_EQ(result->isActive(sd1),true);
  EXPECT_EQ(result->isActive(sd2),false);
  result = arb->execute("D2/NORMAL",true);
  EXPECT_EQ(result->isActive(sd1),true);
  EXPECT_EQ(result->isActive(sd2),true);
}
}

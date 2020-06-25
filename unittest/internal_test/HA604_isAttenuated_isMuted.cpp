// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA604_isAttenuated_isMuted.hpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA604_isAttenuated_isMuted.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

HA604_isAttenuated_isMuted::HA604_isAttenuated_isMuted(void)
{
}

HA604_isAttenuated_isMuted::~HA604_isAttenuated_isMuted(void)
{
}

void HA604_isAttenuated_isMuted::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void HA604_isAttenuated_isMuted::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(HA604_isAttenuated_isMuted, Test_attenuated) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"ナビ",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = { u8"Assert",u8"A",u8"フロント",u8"ナビ"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check zone
    const rba::RBAZone* zone = arb->getModel()->findZone(target);
    ASSERT_NE(nullptr, zone);
    // check visible
    EXPECT_TRUE(result->isSounding(zone));
    EXPECT_EQ(u8"ナビ/NORMAL",result->getContentState(zone)->getUniqueName());
    EXPECT_TRUE(result->isAttenuated(zone));
  }


}
TEST_F(HA604_isAttenuated_isMuted, Test_muted) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = { u8"C",u8"ON",u8"警告音",u8"NORMAL"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = { u8"Assert",u8"A",u8"メインスピーカー",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check zone
    const rba::RBAZone* zone = arb->getModel()->findZone(target);
    ASSERT_NE(nullptr, zone);
    // check invisible
    EXPECT_FALSE(result->isSounding(zone));
    EXPECT_TRUE(result->isMute(zone));
  }

}

}

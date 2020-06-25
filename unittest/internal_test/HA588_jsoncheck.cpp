// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA588_jsoncheck.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA588_jsoncheck.hpp"
#include "TestCommon.hpp"

#ifndef WIN32
namespace {

using namespace rba;

HA588_jsoncheck::HA588_jsoncheck(void)
{
}

HA588_jsoncheck::~HA588_jsoncheck(void)
{
}

void HA588_jsoncheck::SetUp(void)
{
  ofs_ = std::make_unique<std::ofstream>(LOGFILE);
  strbuf_ = std::cerr.rdbuf(ofs_->rdbuf());
}

void HA588_jsoncheck::TearDown(void)
{
  std::cerr.rdbuf( strbuf_ );
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
}

bool HA588_jsoncheck::checkLog(const std::string& str)
{
  std::ifstream ifs(LOGFILE);
  std::string line;
  getline(ifs, line);
  return line.find(str) != std::string::npos;
}

TEST_F(HA588_jsoncheck, nojsonfile)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("UNKNWON_FILE"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("No such file or directory"));
}

// TEST_F(HA588_jsoncheck, oldmodel)
// {
//   rba::RBAJsonParser parser;
//   model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-oldmodel.json"));
//   ASSERT_EQ(nullptr, model_);
//   EXPECT_TRUE(checkLog("arbitrationPolicy not found"));
// }

TEST_F(HA588_jsoncheck, area_nozorder)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-area_nozorder.json"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("zorder not found"));
}

TEST_F(HA588_jsoncheck, area_nopolicy)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-area_nopolicy.json"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("arbitrationPolicy not found"));
}

TEST_F(HA588_jsoncheck, zone_nopriority)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-zone_nopriority.json"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("priority not found"));
}

TEST_F(HA588_jsoncheck, zone_nopolicy)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-zone_nopolicy.json"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("arbitrationPolicy not found"));
}

TEST_F(HA588_jsoncheck, nocontent)
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH("HA588_jsoncheck-nocontent.json"));
  ASSERT_EQ(nullptr, model_);
  EXPECT_TRUE(checkLog("ViewContent or SoundContent not found"));
}

}
#endif

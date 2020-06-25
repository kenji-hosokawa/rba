// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1438_uniqueName.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1438_uniqueName.hpp"
#include "RBAJsonParser.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAViewContent.hpp"

namespace {

void HA1438_uniqueName::SetUp()
{
  rba::RBAJsonParser parser;
  model_
    = dynamic_cast<rba::RBAModelImpl*>(parser.parse(GET_JSON_PATH(JSONFILE)));
  ASSERT_NE(nullptr, model_);
}

void HA1438_uniqueName::TearDown()
{
  if(model_ != nullptr) {
    delete model_;
    model_ = nullptr;
  }
}

/// getName()とgetUniqueName()が一致していることを確認する。
/// getUniqueName()はView/SountContentStateクラスでのみoverwriteしているので、
/// コンテントステート以外のgetUnique()が１つでも確認できれば良いものとする。
TEST_F(HA1438_uniqueName, add_element)
{
  // テスト用のエレメント作成
  rba::RBAAreaImpl* area1 = new rba::RBAAreaImpl("Area1");
  rba::RBAAreaImpl* area2 = new rba::RBAAreaImpl("Area2");

  // 登録を確認
  EXPECT_STREQ("Area1", area1->getUniqueName().c_str());
  EXPECT_STREQ("Area2", area2->getUniqueName().c_str());

  delete area1;
  delete area2;
}

}

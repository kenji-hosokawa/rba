// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1003_hasDisplayingArea.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1003_hasDisplayingArea.hpp"

namespace {

using namespace rba;

HA1003_hasDisplayingArea::HA1003_hasDisplayingArea() {}
HA1003_hasDisplayingArea::~HA1003_hasDisplayingArea() {}

void HA1003_hasDisplayingArea::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1003_hasDisplayingArea::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

TEST_F(HA1003_hasDisplayingArea, Test_01)
{
  const RBADisplay* d1 = model_->findDisplay(u8"Display1");
  const RBADisplay* d2 = model_->findDisplay(u8"Display2");
  const RBADisplay* d3 = model_->findDisplay(u8"Display3");

  // 初期値確認
  result_ = arb_->execute();
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_FALSE(result_->hasDisplayingArea(d1));
  EXPECT_FALSE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当があるエリアの最初のコンテントを表示する
  result_ = arb_->execute(u8"A1");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_FALSE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // すべてのエリアを非表示にする
  result_ = arb_->execute(u8"A1",false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_FALSE(result_->hasDisplayingArea(d1));
  EXPECT_FALSE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当があるエリアの中間のコンテントを表示する
  result_ = arb_->execute(u8"A2");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_FALSE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当があるエリアの最後のコンテントを表示する
  result_ = arb_->execute(u8"A2",false);
  result_ = arb_->execute(u8"A3",true);
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_FALSE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当がある最初エリアを表示する
  result_ = arb_->execute(u8"B1");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当がある複数エリアを表示する
  result_ = arb_->execute(u8"C1");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当がある最後エリアを表示する
  result_ = arb_->execute(u8"B1",false);
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // Displayに割当がある中間エリアを表示する
  result_ = arb_->execute(u8"E1");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_TRUE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_TRUE(result_->hasDisplayingArea(d3));

  // Displayに割当があるエリアを隠蔽する
  result_ = arb_->execute(u8"S1");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_FALSE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_TRUE(result_->hasDisplayingArea(d3));

  // Displayに割当がある非表示エリアを隠蔽する
  result_ = arb_->execute(u8"S2");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_FALSE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_TRUE(result_->hasDisplayingArea(d3));

  // Displayに割当がある表示中エリアを隠蔽する
  result_ = arb_->execute(u8"S5");
  EXPECT_EQ(RBAResultStatusType::SUCCESS,result_->getStatusType());
  EXPECT_FALSE(result_->hasDisplayingArea(d1));
  EXPECT_TRUE(result_->hasDisplayingArea(d2));
  EXPECT_FALSE(result_->hasDisplayingArea(d3));

  // 無効な引数
  EXPECT_FALSE(result_->hasDisplayingArea(nullptr));

}

}

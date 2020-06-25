// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1438_labeledElem.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1438_labeledElem.hpp"
#include "RBAJsonParser.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAViewContent.hpp"

namespace {

void HA1438_labeledElem::SetUp()
{
  rba::RBAJsonParser parser;
  model_
    = dynamic_cast<rba::RBAModelImpl*>(parser.parse(GET_JSON_PATH(JSONFILE)));
  ASSERT_NE(nullptr, model_);
}

void HA1438_labeledElem::TearDown()
{
  if(model_ != nullptr) {
    delete model_;
    model_ = nullptr;
  }
}

/// エレメント追加のテスト
TEST_F(HA1438_labeledElem, add_element)
{
  // テスト用のエレメント作成
  rba::RBAModelElement* elem1 = new rba::RBAAreaImpl("Area1");
  rba::RBAModelElement* elem2 = new rba::RBAAreaImpl("Area2");

  // エレメントの追加
  model_->addLabeledElement("label", elem1);
  model_->addLabeledElement("label", elem2);

  // 登録を確認
  EXPECT_EQ(elem1, model_->getLabeledElements("label").front());
  EXPECT_EQ(elem2, model_->getLabeledElements("label").back());
  EXPECT_EQ(2U, model_->getLabeledElements("label").size());

  delete elem1;
  delete elem2;
}

/// エレメント検索のテスト
TEST_F(HA1438_labeledElem, find_element)
{
  // テスト用のエレメント作成
  rba::RBAModelElement* elem1 = new rba::RBAViewContentImpl("cont1");
  rba::RBAModelElement* elem2 = new rba::RBAViewContentImpl("cont2");
  rba::RBAModelElement* elem3 = new rba::RBAViewContentImpl("cont3");

  // エレメントの追加
  model_->addLabeledElement("labelA", elem1);
  model_->addLabeledElement("labelA", elem2);
  model_->addLabeledElement("labelB", elem3);

  // エレメントの検索（成功）
  const rba::RBAModelElement* e1 = model_->findLabeledElement("labelA",
                                                              "cont1");
  EXPECT_EQ(elem1, e1);
  const rba::RBAModelElement* e2 = model_->findLabeledElement("labelA",
                                                              "cont2");
  EXPECT_EQ(elem2, e2);
  const rba::RBAModelElement* e3 = model_->findLabeledElement("labelB",
                                                              "cont3");
  EXPECT_EQ(elem3, e3);

  // エレメントの検索（失敗）
  const rba::RBAModelElement* e4 = model_->findLabeledElement("UNKNOWN",
                                                              "cont1");
  EXPECT_EQ(nullptr, e4);
  const rba::RBAModelElement* e5 = model_->findLabeledElement("labelA",
                                                              "cont3");
  EXPECT_EQ(nullptr, e5);
  const rba::RBAModelElement* e6 = model_->findLabeledElement("labelB",
                                                              "contq");
  EXPECT_EQ(nullptr, e6);

  delete elem1;
  delete elem2;
  delete elem3;
}

/// 空のエレメントリストのテスト
TEST_F(HA1438_labeledElem, empty_list)
{
  // 空のエレメントリストの取得が成功すること
  std::list<const rba::RBAModelElement*> elems
    = model_->getLabeledElements("UNKNOWN");
  EXPECT_TRUE(elems.empty());
}

}

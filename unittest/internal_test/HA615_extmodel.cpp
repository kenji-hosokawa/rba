// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA615_extmodel.cpp
 */

#include <vector>
#include <string>
#include <memory>
#include "RBAJsonParser.hpp"
#include "RBAModelFactory.hpp"
#include "HA615_extmodel.hpp"
#include "TestCommon.hpp"
#include "HA615_extmodel_sub.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBASoundContentImpl.hpp"

namespace
{

using namespace rba;

HA615_extmodel::HA615_extmodel(void)
{
}

HA615_extmodel::~HA615_extmodel(void)
{
}

void HA615_extmodel::SetUp(void)
{
}

void HA615_extmodel::TearDown(void)
{
}

TEST_F(HA615_extmodel, extmodel)
{
  // 拡張モデルクラスでparseするテスト
  ExtModel* exModel = new ExtModel();
  rba::RBAModelFactory factory(exModel);
  rba::RBAJsonParser parser(&factory);
  rba::RBAModel* model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  EXPECT_EQ(model, exModel);

  // 通常の調停ロジック実行(AllInstanceOfArea.get)のテスト
  rba::RBAArbitrator* arb = new rba::RBAArbitrator(model);

  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  //// コンテンツC1/NORMAL
  result = arb->execute(u8"コンテンツC1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());

  //// Assert エリアA NULL
  {
    std::string target = u8"エリアA";
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  //// Assert エリアB NULL
  {
    std::string target = u8"エリアB";
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    EXPECT_FALSE(result->isVisible(area));
  }

  //// Assert エリアC:コンテンツC1
  {
    std::string target = u8"エリアC";
    std::string expect = u8"コンテンツC1";
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    ASSERT_NE(nullptr, area);
    EXPECT_TRUE(result->isVisible(area));
    const rba::RBAViewContentState* state = result->getContentState(area);
    ASSERT_NE(nullptr, state);
    const rba::RBAViewContent* content = state->getOwner();
    ASSERT_NE(nullptr, content);
    EXPECT_STREQ(expect.c_str(), content->getName().c_str());
  }

  // addContentのテスト
  exModel->setAddContentFlag(false);
  EXPECT_FALSE(exModel->getAddContentFlag());
  std::unique_ptr<rba::RBAViewContentImpl> viewContent
    = std::make_unique<rba::RBAViewContentImpl>("v");
  std::unique_ptr<rba::RBASoundContentImpl> soundContent
    = std::make_unique<rba::RBASoundContentImpl>("s");

  //// addContent(const RBAViewContent*)が呼ばれていることを確認
  exModel->addContent(viewContent.get());
  EXPECT_TRUE(exModel->getAddContentFlag());

  delete exModel;
  delete arb;

}

}

// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA895_size.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA895_size.hpp"

namespace {

using namespace rba;

HA895_size::HA895_size() {}
HA895_size::~HA895_size() {}

void HA895_size::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
}

void HA895_size::TearDown()
{
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
}

TEST_F(HA895_size, get_name)
{
  // Display size
  {
    const std::string displayName = u8"SampleDisplay";
    std::string sizeName = u8"FullScreen";
    int width = 500;
    int height = 200;
    {
      // ディスプレイのサイズはモデルに登録されない
      const RBASize* sizeObj = model_->findSize(sizeName);
      EXPECT_EQ(nullptr, sizeObj);
    }
    {
      // ディスプレイのサイズは自分で持つ
      const RBADisplay* display = model_->findDisplay(displayName);
      const RBASize* sizeObj = display->getSize();
      EXPECT_NE(nullptr, sizeObj);
      EXPECT_STREQ(sizeName.c_str(), sizeObj->getName().c_str());
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }

  {
    std::string sizeName = u8"SizeA";
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_EQ(nullptr, sizeObj);
  }
  {
    std::string sizeName = u8"SizeCommon";
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_EQ(nullptr, sizeObj);
  }
  {
    std::string sizeName = u8"AreaA/SizeA";
    int width = 200;
    int height = 100;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"AreaA/SizeCommon";
    int width = 100;
    int height = 200;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"AreaB/SizeA";
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_EQ(nullptr, sizeObj);
  }
  {
    std::string sizeName = u8"AreaB/SizeCommon";
    int width = 300;
    int height = 200;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"cont1/SizeA";
    int width = 100;
    int height = 50;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"cont1/SizeCommon";
    int width = 105;
    int height = 55;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"cont2/SizeA";
    int width = 200;
    int height = 300;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
  {
    std::string sizeName = u8"cont2/SizeCommon";
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_EQ(nullptr, sizeObj);
  }
  {
    std::string sizeName = u8"cont3/SizeA";
    int width = 50;
    int height = 40;
    const RBASize* sizeObj = model_->findSize(sizeName);
    EXPECT_NE(nullptr, sizeObj);
    if(sizeObj) {
      EXPECT_EQ(width, sizeObj->getWidth());
      EXPECT_EQ(height, sizeObj->getHeight());
    }
  }
}

}

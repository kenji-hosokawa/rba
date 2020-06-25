/// @file  HA1438_labeledElem.hpp
/// @brief ラベル付きのエレメントの単体テストヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef HA1438_LABELEDELEM_HPP
#define HA1438_LABELEDELEM_HPP

#include <string>
#include "gtest/gtest.h"

// JSONファイルのモデル情報は使用しないので、
// AllInstanceOfArea.jsonを流用。
#define JSONFILE	"HA1438_labeledElem.json"

namespace rba
{
class RBAModelImpl;
}

namespace {

using namespace rba;

class HA1438_labeledElem : public ::testing::Test
{
protected:
  HA1438_labeledElem()=default;
  virtual ~HA1438_labeledElem()=default;
  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModelImpl* model_=nullptr;

};

}
#endif

/// @file  HA1438_uniqueName.hpp
/// @brief uniqueNameの単体テストヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef HA1438_LABELEDELEM_HPP
#define HA1438_LABELEDELEM_HPP

#include <string>
#include "gtest/gtest.h"

// AllInstanceOfArea.jsonを流用している
// labeledElemのJSONを使用。
#define JSONFILE	"HA1438_labeledElem.json"

namespace rba
{
class RBAModelImpl;
}

namespace {

using namespace rba;

class HA1438_uniqueName : public ::testing::Test
{
protected:
  HA1438_uniqueName()=default;
  virtual ~HA1438_uniqueName()=default;
  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModelImpl* model_=nullptr;

};

}
#endif

/// @file  RBAObjectCompareMaker.cpp
/// @brief ObjectCompareオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAObjectCompareMaker.hpp"
#include "RBAObjectCompare.hpp"

namespace rba
{

RBAObjectCompareMaker::RBAObjectCompareMaker()
  : RBAOperatorMaker{"ObjectCompare"}
{
}

std::unique_ptr<RBAModelElement>
RBAObjectCompareMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAObjectCompare>();
}

}

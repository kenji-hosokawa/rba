/// @file  RBAIsGreaterThanEqualOperatorMaker.cpp
/// @brief IsGreaterThanEqualOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsGreaterThanOperatorMaker.hpp"
#include "RBAIsGreaterThanOperator.hpp"

namespace rba
{

RBAIsGreaterThanOperatorMaker::RBAIsGreaterThanOperatorMaker()
  : RBAOperatorMaker{"IsGreaterThanOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsGreaterThanOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsGreaterThanOperator>();
}

}

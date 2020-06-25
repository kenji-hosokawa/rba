/// @file  RBAIsGreaterThanEqualOperatorMaker.cpp
/// @brief IsGreaterThanEqualOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsGreaterThanEqualOperatorMaker.hpp"
#include "RBAIsGreaterThanEqualOperator.hpp"

namespace rba
{

RBAIsGreaterThanEqualOperatorMaker::RBAIsGreaterThanEqualOperatorMaker()
  : RBAOperatorMaker{"IsGreaterThanEqualOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsGreaterThanEqualOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsGreaterThanEqualOperator>();
}

}

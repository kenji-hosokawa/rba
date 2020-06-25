/// @file  RBAIsLowerThanEqualOperatorMaker.cpp
/// @brief IsLowerThanEqualOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsLowerThanEqualOperatorMaker.hpp"
#include "RBAIsLowerThanEqualOperator.hpp"

namespace rba
{

RBAIsLowerThanEqualOperatorMaker::RBAIsLowerThanEqualOperatorMaker()
  : RBAOperatorMaker{"IsLowerThanEqualOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsLowerThanEqualOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsLowerThanEqualOperator>();
}

}

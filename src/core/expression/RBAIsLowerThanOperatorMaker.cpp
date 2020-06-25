/// @file  RBAIsLowerThanOperatorMaker.cpp
/// @brief IsLowerThanOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsLowerThanOperatorMaker.hpp"
#include "RBAIsLowerThanOperator.hpp"

namespace rba
{

RBAIsLowerThanOperatorMaker::RBAIsLowerThanOperatorMaker()
  : RBAOperatorMaker{"IsLowerThanOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsLowerThanOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsLowerThanOperator>();
}

}

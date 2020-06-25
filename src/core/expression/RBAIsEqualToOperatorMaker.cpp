/// @file  RBAIsEqualToOperatorMaker.cpp
/// @brief IsEqualToOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsEqualToOperatorMaker.hpp"
#include "RBAIsEqualToOperator.hpp"

namespace rba
{

RBAIsEqualToOperatorMaker::RBAIsEqualToOperatorMaker()
  : RBAOperatorMaker{"IsEqualToOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsEqualToOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsEqualToOperator>();
}

}

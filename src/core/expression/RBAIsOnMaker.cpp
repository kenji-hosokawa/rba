/// @file  RBAIsOnMaker.cpp
/// @brief IsOnオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsOnMaker.hpp"
#include "RBAIsOn.hpp"

namespace rba
{

RBAIsOnMaker::RBAIsOnMaker()
  : RBAOperatorMaker{"IsOn"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsOnMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsOn>();
}

}

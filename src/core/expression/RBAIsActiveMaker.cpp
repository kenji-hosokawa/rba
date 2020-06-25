/// @file  RBAIsActiveMaker.cpp
/// @brief IsActiveオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsActiveMaker.hpp"
#include "RBAIsActive.hpp"

namespace rba
{

RBAIsActiveMaker::RBAIsActiveMaker()
  : RBAOperatorMaker{"IsActive"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsActiveMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsActive>();
}

}

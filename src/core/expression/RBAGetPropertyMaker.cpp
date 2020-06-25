/// @file  RBAGetPropertyMaker.cpp
/// @brief GetPropertyオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAGetPropertyMaker.hpp"
#include "RBAGetProperty.hpp"

namespace rba
{

RBAGetPropertyMaker::RBAGetPropertyMaker()
  : RBAOperatorMaker{"GetProperty"}
{
}

std::unique_ptr<RBAModelElement>
RBAGetPropertyMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAGetProperty>();
}

}

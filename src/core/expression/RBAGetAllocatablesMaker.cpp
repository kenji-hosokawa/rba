/// @file  RBAGetAllocatablesMaker.cpp
/// @brief GetAllocatablesオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAGetAllocatablesMaker.hpp"
#include "RBAGetAllocatables.hpp"

namespace rba
{

RBAGetAllocatablesMaker::RBAGetAllocatablesMaker()
  : RBAOperatorMaker{"GetAllocatables"}
{
}

std::unique_ptr<RBAModelElement>
RBAGetAllocatablesMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAGetAllocatables>();
}

}

/// @file  RBAIsVisibleMaker.cpp
/// @brief IsVisibleオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAIsVisibleMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsVisible.hpp"

namespace rba
{

RBAIsVisibleMaker::RBAIsVisibleMaker()
  : RBAOperatorMaker{"IsVisible"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsVisibleMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsVisible>();
}

}

/// @file  RBAIsHiddenMaker.cpp
/// @brief IsHiddenオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAIsHiddenMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsHidden.hpp"

namespace rba
{

RBAIsHiddenMaker::RBAIsHiddenMaker()
  : RBAOperatorMaker{"IsHidden"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsHiddenMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsHidden>();
}

}

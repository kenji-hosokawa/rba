/// @file  RBAIsDisplayedMaker.cpp
/// @brief IsDisplayedオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAIsDisplayedMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsDisplayed.hpp"

namespace rba
{

RBAIsDisplayedMaker::RBAIsDisplayedMaker()
  : RBAOperatorMaker{"IsDisplayed"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsDisplayedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsDisplayed>();
}

}

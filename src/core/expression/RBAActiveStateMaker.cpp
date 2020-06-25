/// @file  RBAActiveStateMaker.cpp
/// @brief ActiveStateオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAActiveStateMaker.hpp"
#include "RBAActiveState.hpp"

namespace rba
{

RBAActiveStateMaker::RBAActiveStateMaker()
  : RBAOperatorMaker{"ActiveState"}
{
}

std::unique_ptr<RBAModelElement>
RBAActiveStateMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAActiveState>();
}

}

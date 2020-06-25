/// @file  RBAViewContentStateMaker.cpp
/// @brief ViewContentStateオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAViewContentStateMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAViewContentStateMaker::RBAViewContentStateMaker()
  : RBAContentStateMaker{"ViewContentState"}
{
}

std::unique_ptr<RBAModelElement>
RBAViewContentStateMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAViewContentStateImpl>(name);
}

}


/// @file  RBAIsMutedMaker.cpp
/// @brief IsMutedオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsMutedMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsMuted.hpp"

namespace rba
{

RBAIsMutedMaker::RBAIsMutedMaker()
  : RBAOperatorMaker{"IsMuted"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsMutedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsMuted>();
}

}

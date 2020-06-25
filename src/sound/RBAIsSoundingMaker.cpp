/// @file  RBAIsSoundingMaker.cpp
/// @brief IsSoundingオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIsSoundingMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsSounding.hpp"

namespace rba
{

RBAIsSoundingMaker::RBAIsSoundingMaker()
  : RBAOperatorMaker{"IsSounding"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsSoundingMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsSounding>();
}

}

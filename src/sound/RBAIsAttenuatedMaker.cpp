/// @file  RBAIsAttenuatedMaker.cpp
/// @brief IsAttenuatedオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAIsAttenuatedMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsAttenuated.hpp"

namespace rba
{

RBAIsAttenuatedMaker::RBAIsAttenuatedMaker()
  : RBAOperatorMaker{"IsAttenuated"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsAttenuatedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsAttenuated>();
}

}

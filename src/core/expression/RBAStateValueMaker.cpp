/// @file  RBAStateValueMaker.cpp
/// @brief StateValueオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAStateValueMaker.hpp"
#include "RBAStateValue.hpp"

namespace rba
{

RBAStateValueMaker::RBAStateValueMaker()
  : RBAOperatorMaker{"StateValue"}
{
}

std::unique_ptr<RBAModelElement>
RBAStateValueMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAStateValue>();
}

}

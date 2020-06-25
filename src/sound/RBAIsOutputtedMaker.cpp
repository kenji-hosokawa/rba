/// @file  RBAIsOutputtedMaker.cpp
/// @brief IsOutputtedオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAIsOutputtedMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAIsOutputted.hpp"

namespace rba
{

RBAIsOutputtedMaker::RBAIsOutputtedMaker()
  : RBAOperatorMaker{"IsOutputted"}
{
}

std::unique_ptr<RBAModelElement>
RBAIsOutputtedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIsOutputted>();
}


}

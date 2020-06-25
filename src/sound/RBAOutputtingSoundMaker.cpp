/// @file  RBAOutputtingSoundMaker.cpp
/// @brief OutputtingSoundオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAOutputtingSoundMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAOutputtingSound.hpp"

namespace rba
{

RBAOutputtingSoundMaker::RBAOutputtingSoundMaker()
  : RBAOperatorMaker{"OutputtingSound"}
{
}

std::unique_ptr<RBAModelElement>
RBAOutputtingSoundMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAOutputtingSound>();
}

}

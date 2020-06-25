/// @file  RBAHasBeenDisplayedMaker.cpp
/// @brief HasBeenDisplayedオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAHasBeenDisplayedMaker.hpp"
#include "RBAHasBeenDisplayed.hpp"

namespace rba
{

RBAHasBeenDisplayedMaker::RBAHasBeenDisplayedMaker()
  : RBAOperatorMaker{"HasBeenDisplayed"}
{
}

std::unique_ptr<RBAModelElement>
RBAHasBeenDisplayedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAHasBeenDisplayed>();
}

}

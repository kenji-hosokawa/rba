/// @file  RBADisplayingContentMaker.cpp
/// @brief DisplayingContentオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBADisplayingContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBADisplayingContent.hpp"

namespace rba
{

RBADisplayingContentMaker::RBADisplayingContentMaker()
  : RBAOperatorMaker{"DisplayingContent"}
{
}

std::unique_ptr<RBAModelElement>
RBADisplayingContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBADisplayingContent>();
}

}

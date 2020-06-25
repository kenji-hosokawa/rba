/// @file  RBAGetContentsListMaker.cpp
/// @brief GetContentsListオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAGetContentsListMaker.hpp"
#include "RBAGetContentsList.hpp"

namespace rba
{

RBAGetContentsListMaker::RBAGetContentsListMaker()
  : RBAOperatorMaker{"GetContentsList"}
{
}

std::unique_ptr<RBAModelElement>
RBAGetContentsListMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAGetContentsList>();
}

}

/// @file  RBAAllocatedContentMaker.cpp
/// @brief AllocatedContentオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAllocatedContentMaker.hpp"
#include "RBAAllocatedContent.hpp"

namespace rba
{

RBAAllocatedContentMaker::RBAAllocatedContentMaker()
  : RBAOperatorMaker{"AllocatedContent"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllocatedContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllocatedContent>();
}

}

/// @file  RBAAllocatedContentMaker.cpp
/// @brief AllocatedContent object maker class definition
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

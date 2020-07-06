/// @file  RBAActiveContentsMaker.cpp
/// @brief ActiveContents object creation class defintion
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAActiveContentsMaker.hpp"
#include "RBAActiveContents.hpp"

namespace rba
{

RBAActiveContentsMaker::RBAActiveContentsMaker()
  : RBAOperatorMaker{"ActiveContents"}
{
}

std::unique_ptr<RBAModelElement>
RBAActiveContentsMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAActiveContents>();
}

}

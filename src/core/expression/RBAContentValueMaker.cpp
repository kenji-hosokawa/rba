/// @file  RBAContentValueMaker.cpp
/// @brief ContentValue object maker classs definition
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAContentValueMaker.hpp"
#include "RBAContentValue.hpp"

namespace rba
{

RBAContentValueMaker::RBAContentValueMaker()
  : RBAOperatorMaker{"ContentValue"}
{
}

std::unique_ptr<RBAModelElement>
RBAContentValueMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAContentValue>();
}


}

/// @file  RBAHasComeEarlierThanMaker.cpp
/// @brief HasComeEarlierThanオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAHasComeEarlierThanMaker.hpp"
#include "RBAHasComeEarlierThan.hpp"

namespace rba
{

RBAHasComeEarlierThanMaker::RBAHasComeEarlierThanMaker()
  : RBAOperatorMaker{"HasComeEarlierThan"}
{
}

std::unique_ptr<RBAModelElement>
RBAHasComeEarlierThanMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAHasComeEarlierThan>();
}

}

/// @file  RBAHasComeLaterThanMaker.cpp
/// @brief HasComeLaterThanオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAHasComeLaterThanMaker.hpp"
#include "RBAHasComeLaterThan.hpp"

namespace rba
{

RBAHasComeLaterThanMaker::RBAHasComeLaterThanMaker()
  : RBAOperatorMaker{"HasComeLaterThan"}
{
}

std::unique_ptr<RBAModelElement>
RBAHasComeLaterThanMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAHasComeLaterThan>();
}

}

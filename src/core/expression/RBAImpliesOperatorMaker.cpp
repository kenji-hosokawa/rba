/// @file  RBAImpliesOperatorMaker.cpp
/// @brief ImpliesOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAImpliesOperatorMaker.hpp"
#include "RBAImpliesOperator.hpp"

namespace rba
{

RBAImpliesOperatorMaker::RBAImpliesOperatorMaker()
  : RBAOperatorMaker{"ImpliesOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAImpliesOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAImpliesOperator>();
}

}

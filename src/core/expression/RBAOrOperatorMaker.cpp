/// @file  RBAOrOperatorMaker.cpp
/// @brief OrOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAOrOperatorMaker.hpp"
#include "RBAOrOperator.hpp"

namespace rba
{

RBAOrOperatorMaker::RBAOrOperatorMaker()
  : RBAOperatorMaker{"OrOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAOrOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAOrOperator>();
}

}

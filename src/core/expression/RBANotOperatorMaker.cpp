/// @file  RBANotOperatorMaker.cpp
/// @brief NotOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBANotOperatorMaker.hpp"
#include "RBANotOperator.hpp"

namespace rba
{

RBANotOperatorMaker::RBANotOperatorMaker()
  : RBAOperatorMaker{"NotOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBANotOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBANotOperator>();
}

}

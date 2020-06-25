/// @file  RBAPlusOperatorsMaker.cpp
/// @brief PlusOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAPlusOperatorMaker.hpp"
#include "RBAPlusOperator.hpp"

namespace rba
{

RBAPlusOperatorMaker::RBAPlusOperatorMaker()
  : RBAOperatorMaker{"PlusOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAPlusOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAPlusOperator>();
}

}

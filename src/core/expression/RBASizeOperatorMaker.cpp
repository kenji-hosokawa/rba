/// @file  RBASizeOperatorMaker.cpp
/// @brief SizeOperatorオブジェクト生成抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASizeOperatorMaker.hpp"
#include "RBASizeOperator.hpp"

namespace rba
{

RBASizeOperatorMaker::RBASizeOperatorMaker()
  : RBAOperatorMaker{"SizeOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBASizeOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASizeOperator>();
}

}

/// @file  RBASetOfOperatorMaker.cpp
/// @brief SetOfOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBASetOfOperatorMaker.hpp"
#include "RBASetOfOperator.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContentSet.hpp"

namespace rba
{

RBASetOfOperatorMaker::RBASetOfOperatorMaker()
  : RBAOperatorMaker{"SetOfOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBASetOfOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASetOfOperator>();
}

}

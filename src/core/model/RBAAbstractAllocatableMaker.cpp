/// @file  RBAAbstractAllocatableMaker.cpp
/// @brief 抽象アロケータブル生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAbstractAllocatableMaker.hpp"
#include "RBAAbstractAllocatable.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAbstractAllocatableMaker::RBAAbstractAllocatableMaker(const std::string& label)
  : RBARuleObjectMaker{label}
{
}

RBAModelElement*
RBAAbstractAllocatableMaker::setProperty(RBAModelElement* element,
                                         const RBAJsonElement* jsonElem,
                                         RBAModelImpl* model,
                                         RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));
  
  const auto abstAllo = dynamic_cast<RBAAbstractAllocatable*>(element);

  // 現在、モデル情報としてRBAAbstractAllocatableMakerでセットするメンバはないが、
  // 今後追加される可能性があるのでこの処理は残しておく。

  return abstAllo;
}

}

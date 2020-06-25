/// @file  RBAAbstractContentMaker.cpp
/// @brief 抽象アロケータブル生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAbstractContentMaker.hpp"
#include "RBAAbstractContent.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAbstractContentMaker::RBAAbstractContentMaker(const std::string& label)
  : RBARuleObjectMaker{label}
{
}

RBAModelElement*
RBAAbstractContentMaker::setProperty(RBAModelElement* element,
                                     const RBAJsonElement* jsonElem,
                                     RBAModelImpl* model,
                                     RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));
  
  const auto abstContent = dynamic_cast<RBAAbstractContent*>(element);

  // 現在、モデル情報としてRBAAbstractContentMakerでセットするメンバはないが、
  // 今後追加される可能性があるのでこの処理は残しておく。

  return abstContent;
}

}

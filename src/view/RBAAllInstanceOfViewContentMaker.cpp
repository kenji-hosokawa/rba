/// @file  RBAAllInstanceOfViewContentMaker.cpp
/// @brief AllInstanceOfViewContentaオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include <iostream>
#include "RBAAllInstanceOfViewContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfViewContent.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfViewContentMaker::RBAAllInstanceOfViewContentMaker()
  : RBAExpressionMaker{"AllInstanceOfViewContent"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfViewContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfViewContent>();
}

RBAModelElement*
RBAAllInstanceOfViewContentMaker::setProperty(RBAModelElement* element,
                                              const RBAJsonElement* jsonElem,
                                              RBAModelImpl* model,
                                              RBAModelElement* owner)
{
  RBAAllInstanceOfViewContent* const allCont
    {dynamic_cast<RBAAllInstanceOfViewContent*>(element)};
  allCont->setContents(model->getViewContentImpls());

  return allCont;
}

}

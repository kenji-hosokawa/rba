/// @file  RBAAbstractConstraintMaker.cpp
/// @brief 抽象制約式オブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAbstractConstraintMaker.hpp"
#include "RBAAbstractConstraint.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAbstractConstraintMaker::RBAAbstractConstraintMaker(const std::string& label)
  : RBAModelElementMaker{label}
{
}

RBAModelElement*
RBAAbstractConstraintMaker::setProperty(RBAModelElement* element,
                                        const RBAJsonElement* jsonElem,
                                        RBAModelImpl* model,
                                        RBAModelElement* owner)
{
  const auto abstConstraint = dynamic_cast<RBAAbstractConstraint*>(element);

  // Set expression
  const RBAJsonElement* const childElem {jsonElem->findChildren("expression")};
  RBAModelElement* const expr {getFactory()->createElement(childElem->getClassName(),
                                                  childElem)};
  abstConstraint->setExpression(dynamic_cast<RBAExpression*>(expr));

  return abstConstraint;
}

}

/// @file  RBAIntegerValueMaker.cpp
/// @brief IntegerValueオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAIntegerValueMaker.hpp"
#include "RBAIntegerValue.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAIntegerValueMaker::RBAIntegerValueMaker()
  : RBAExpressionMaker{"IntegerValue"}
{
}

std::unique_ptr<RBAModelElement>
RBAIntegerValueMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIntegerValue>();
}

RBAModelElement*
RBAIntegerValueMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  RBAIntegerValue* const intVal {dynamic_cast<RBAIntegerValue*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, intVal, jsonElem)};

  // Set value
  const RBAJsonElement* const valueElem {jsonElem->findChildren("value")};
  intVal->setValue(stoi(valueElem->getString()));

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return intVal;
}

}

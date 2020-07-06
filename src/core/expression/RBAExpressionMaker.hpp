/// @file  RBAExpreessionMaker.hpp
/// @brief Abstract class definition header file for expression object generation
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAEXPRESSIONMAKER_HPP
#define RBAEXPRESSIONMAKER_HPP

#include <cstdint>
#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAExpression;

/// @brief Abstract class for expression object gcreation
class DLL_EXPORT RBAExpressionMaker : public RBAModelElementMaker
{
public:
  explicit RBAExpressionMaker(const std::string& label="");
  RBAExpressionMaker(const RBAExpressionMaker&)=delete;
  RBAExpressionMaker(const RBAExpressionMaker&&)=delete;
  RBAExpressionMaker& operator=(const RBAExpressionMaker&)=delete;
  RBAExpressionMaker& operator=(const RBAExpressionMaker&&)=delete;
  virtual ~RBAExpressionMaker()=default;

protected:
  /// @brief To set ”Let" expression
  /// @details Generate Let expression from jsonElem and register it in expr.
  ///          Return the number of variables that have been registered
  ///          (pushed) to ModelFactory, and pop them when the reference of 
  ///          variables is completed in function that called this function.
  ///          ModelFactoryに登録(push)した変数の数を返し、本関数を呼び出した処理で、
  ///          変数の参照が完了したタイミングでpopしておくこと。
  /// @return the number of pushed variables
  std::int32_t setLetStatement(RBAModelImpl* model,
                               RBAExpression* expr,
                               const RBAJsonElement* jsonElem);

};

}

#endif

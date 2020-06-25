/// @file  RBAExpreessionMaker.hpp
/// @brief Expressionオブジェクト生成の抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAEXPRESSIONMAKER_HPP
#define RBAEXPRESSIONMAKER_HPP

#include <cstdint>
#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAExpression;

/// @brief Expressionオブジェクト生成の抽象クラス
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
  /// @brief Let式をセットする
  /// @details jsonElemからLet式を生成し、exprに登録する。
  ///          ModelFactoryに登録(push)した変数の数を返し、本関数を呼び出した処理で、
  ///          変数の参照が完了したタイミングでpopしておくこと。
  /// @return pushした変数の数
  std::int32_t setLetStatement(RBAModelImpl* model,
                               RBAExpression* expr,
                               const RBAJsonElement* jsonElem);

};

}

#endif

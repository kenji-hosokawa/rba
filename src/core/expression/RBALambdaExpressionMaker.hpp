/// @file  RBALambdaExpressionMaker.hpp
/// @brief LambdaExpressionオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBALAMBDAEXPRESSIONMAKER_HPP
#define RBALAMBDAEXPRESSIONMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief LambdaExpressionオブジェクト生成クラス
class RBALambdaExpressionMaker : public RBAExpressionMaker
{
public:
  RBALambdaExpressionMaker();
  RBALambdaExpressionMaker(const RBALambdaExpressionMaker&)=delete;
  RBALambdaExpressionMaker(const RBALambdaExpressionMaker&&)=delete;
  RBALambdaExpressionMaker& operator=(const RBALambdaExpressionMaker&)=delete;
  RBALambdaExpressionMaker& operator=(const RBALambdaExpressionMaker&&)=delete;
  virtual ~RBALambdaExpressionMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief 派生クラスごとにモデルエレメントの属性をセットする
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner=nullptr) override;

};

}

#endif

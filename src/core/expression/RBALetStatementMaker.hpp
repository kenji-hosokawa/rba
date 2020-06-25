/// @file  RBALetStatementMaker.hpp
/// @brief LetStatementオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISACTIVEMAKER_HPP
#define RBAISACTIVEMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief LetStatementオブジェクト生成クラス
class RBALetStatementMaker : public RBAExpressionMaker
{
public:
  RBALetStatementMaker();
  RBALetStatementMaker(const RBALetStatementMaker&)=delete;
  RBALetStatementMaker(const RBALetStatementMaker&&)=delete;
  RBALetStatementMaker& operator=(const RBALetStatementMaker&)=delete;
  RBALetStatementMaker& operator=(const RBALetStatementMaker&&)=delete;
  virtual ~RBALetStatementMaker()=default;

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
                                       RBAModelElement* owner) override;

};

}

#endif
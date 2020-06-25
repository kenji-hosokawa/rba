/// @file  RBAIfStatementMaker.hpp
/// @brief IfStatementオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAIFSTATEMENTMAKER_HPP
#define RBAIFSTATEMENTMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief IfStatementオブジェクト生成クラス
class RBAIfStatementMaker : public RBAExpressionMaker
{
public:
  RBAIfStatementMaker();
  RBAIfStatementMaker(const RBAIfStatementMaker&)=delete;
  RBAIfStatementMaker(const RBAIfStatementMaker&&)=delete;
  RBAIfStatementMaker& operator=(const RBAIfStatementMaker&)=delete;
  RBAIfStatementMaker& operator=(const RBAIfStatementMaker&&)=delete;
  virtual ~RBAIfStatementMaker()=default;

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

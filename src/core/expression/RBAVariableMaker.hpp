/// @file  RBAVariableMaker.hpp
/// @brief 変数オブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAVARIABLEMAKER_HPP
#define RBAVARIABLEMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

/// @brief 変数オブジェクト生成クラス
class RBAVariableMaker : public RBAModelElementMaker
{
public:
  RBAVariableMaker();
  RBAVariableMaker(const RBAVariableMaker&)=delete;
  RBAVariableMaker(const RBAVariableMaker&&)=delete;
  RBAVariableMaker& operator=(const RBAVariableMaker&)=delete;
  RBAVariableMaker& operator=(const RBAVariableMaker&&)=delete;
  virtual ~RBAVariableMaker()=default;

public:
  /// @brief ModelElementオブジェクト生成
  /// @details ModelElementオブジェクトを生成して、unique_ptrをmodelに登録する。
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  /// @return ModelElementオブジェクト
  RBAModelElement* create(const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner=nullptr) override;

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

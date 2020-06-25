/// @file  RBAConstraintMaker.jhp
/// @brief 制約式オブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACONSTRAINTMAKER_HPP
#define RBACONSTRAINTMAKER_HPP

#include "RBAAbstractConstraintMaker.hpp"

namespace rba
{

/// @brief 制約式オブジェクト生成クラス
class RBAConstraintMaker : public RBAAbstractConstraintMaker
{
public:
  RBAConstraintMaker();
  RBAConstraintMaker(const RBAConstraintMaker&)=delete;
  RBAConstraintMaker(const RBAConstraintMaker&&)=delete;
  RBAConstraintMaker& operator=(const RBAConstraintMaker&)=delete;
  RBAConstraintMaker& operator=(const RBAConstraintMaker&&)=delete;
  virtual ~RBAConstraintMaker()=default;

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

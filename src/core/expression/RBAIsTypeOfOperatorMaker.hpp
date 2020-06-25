/// @file  RBAIsTypeOfOperatorMaker.hpp
/// @brief IsTypeOfオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISTYPEOFOPERATORMAKER_HPP
#define RBAISTYPEOFOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ObjectCompareオブジェクト生成クラス
class RBAIsTypeOfOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsTypeOfOperatorMaker();
  RBAIsTypeOfOperatorMaker(const RBAIsTypeOfOperatorMaker&)=delete;
  RBAIsTypeOfOperatorMaker(const RBAIsTypeOfOperatorMaker&&)=delete;
  RBAIsTypeOfOperatorMaker& operator=(const RBAIsTypeOfOperatorMaker&)=delete;
  RBAIsTypeOfOperatorMaker& operator=(const RBAIsTypeOfOperatorMaker&&)=delete;
  virtual ~RBAIsTypeOfOperatorMaker()=default;

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

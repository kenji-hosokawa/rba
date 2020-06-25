/// @file  RBAIntegerValueMaker.hpp
/// @brief IntegerValueオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAINTEGERVALUEMAKER_HPP
#define RBAINTEGERVALUEMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief IntegerValueオブジェクト生成クラス
class RBAIntegerValueMaker : public RBAExpressionMaker
{
public:
  RBAIntegerValueMaker();
  RBAIntegerValueMaker(const RBAIntegerValueMaker&)=delete;
  RBAIntegerValueMaker(const RBAIntegerValueMaker&&)=delete;
  RBAIntegerValueMaker& operator=(const RBAIntegerValueMaker&)=delete;
  RBAIntegerValueMaker& operator=(const RBAIntegerValueMaker&&)=delete;
  virtual ~RBAIntegerValueMaker()=default;

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

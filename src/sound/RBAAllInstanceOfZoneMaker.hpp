/// @file  RBAAllInstanceOfZoneMaker.hpp
/// @brief AllInstanceOfZoneオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLINSTANCEOFZONEMAKER_HPP
#define RBAALLINSTANCEOFZONEMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief AllInstanceOfZoneオブジェクト生成クラス
class RBAAllInstanceOfZoneMaker : public RBAExpressionMaker
{
public:
  RBAAllInstanceOfZoneMaker();
  RBAAllInstanceOfZoneMaker(const RBAAllInstanceOfZoneMaker&)=delete;
  RBAAllInstanceOfZoneMaker(const RBAAllInstanceOfZoneMaker&&)=delete;
  RBAAllInstanceOfZoneMaker& operator=(const RBAAllInstanceOfZoneMaker&)=delete;
  RBAAllInstanceOfZoneMaker& operator=(const RBAAllInstanceOfZoneMaker&&)=delete;
  virtual ~RBAAllInstanceOfZoneMaker()=default;

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

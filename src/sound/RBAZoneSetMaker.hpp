/// @file  RBAZoneSetMaker.hpp
/// @brief ZoneSetオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAZONESETMAKER_HPP
#define RBAZONESETMAKER_HPP

#include "RBAAllocatableSetMaker.hpp"

namespace rba
{

/// @brief ZoneSetオブジェクト生成クラス
class RBAZoneSetMaker : public RBAAllocatableSetMaker
{
public:
  RBAZoneSetMaker();
  RBAZoneSetMaker(const RBAZoneSetMaker&)=delete;
  RBAZoneSetMaker(const RBAZoneSetMaker&&)=delete;
  RBAZoneSetMaker& operator=(const RBAZoneSetMaker&)=delete;
  RBAZoneSetMaker& operator=(const RBAZoneSetMaker&&)=delete;
  virtual ~RBAZoneSetMaker()=default;

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

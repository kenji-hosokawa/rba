/// @file  RBAAreaSetMaker.hpp
/// @brief AreaSetオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAAREASETMAKER_HPP
#define RBAAREASETMAKER_HPP

#include "RBAAllocatableSetMaker.hpp"

namespace rba
{

/// @brief AreaSetオブジェクト生成クラス
class RBAAreaSetMaker : public RBAAllocatableSetMaker
{
public:
  RBAAreaSetMaker();
  RBAAreaSetMaker(const RBAAreaSetMaker&)=delete;
  RBAAreaSetMaker(const RBAAreaSetMaker&&)=delete;
  RBAAreaSetMaker& operator=(const RBAAreaSetMaker&)=delete;
  RBAAreaSetMaker& operator=(const RBAAreaSetMaker&&)=delete;
  virtual ~RBAAreaSetMaker()=default;

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

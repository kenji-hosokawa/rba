/// @file  RBAAreaMaker.hpp
/// @brief Areaオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAAREAMAKER_HPP
#define RBAAREAMAKER_HPP

#include "RBAAllocatableMaker.hpp"

namespace rba
{

/// @brief Areaオブジェクト生成クラス
class RBAAreaMaker : public RBAAllocatableMaker
{
public:
  RBAAreaMaker();
  RBAAreaMaker(const RBAAreaMaker&)=default;
  RBAAreaMaker& operator=(const RBAAreaMaker&)=default;
  // move削除
  RBAAreaMaker(const RBAAreaMaker&&)=delete;
  RBAAreaMaker& operator=(const RBAAreaMaker&&)=delete;
  virtual ~RBAAreaMaker()=default;

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

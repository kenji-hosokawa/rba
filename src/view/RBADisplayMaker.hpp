/// @file  RBADisplayMaker.hpp
/// @brief Displayオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBADISPLAYMAKER_HPP
#define RBADISPLAYMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief Displayオブジェクト生成クラス
class RBADisplayMaker : public RBAModelElementMaker
{
public:
  RBADisplayMaker();
  RBADisplayMaker(const RBADisplayMaker&)=delete;
  RBADisplayMaker(const RBADisplayMaker&&)=delete;
  RBADisplayMaker& operator=(const RBADisplayMaker&)=delete;
  RBADisplayMaker& operator=(const RBADisplayMaker&&)=delete;
  virtual ~RBADisplayMaker()=default;

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

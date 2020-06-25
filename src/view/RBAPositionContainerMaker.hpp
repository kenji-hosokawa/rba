/// @file  RBAPositionContainerMaker.hpp
/// @brief PositionContainerオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAPOSITIONCONTAINERMAKER_HPP
#define RBAPOSITIONCONTAINERMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief PositionContainerオブジェクト生成クラス
class RBAPositionContainerMaker : public RBAModelElementMaker
{
public:
  RBAPositionContainerMaker();
  RBAPositionContainerMaker(const RBAPositionContainerMaker&)=delete;
  RBAPositionContainerMaker(const RBAPositionContainerMaker&&)=delete;
  RBAPositionContainerMaker& operator=(const RBAPositionContainerMaker&)=delete;
  RBAPositionContainerMaker& operator=(const RBAPositionContainerMaker&&)=delete;
  virtual ~RBAPositionContainerMaker()=default;

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

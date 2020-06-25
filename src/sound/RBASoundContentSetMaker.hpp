/// @file  RBASoundContentSetMaker.hpp
/// @brief SoundContentSetオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASOUNDCONTENTSETMAKER_HPP
#define RBASOUNDCONTENTSETMAKER_HPP

#include "RBAContentSetMaker.hpp"

namespace rba
{

/// @brief SoundContentSetオブジェクト生成クラス
class RBASoundContentSetMaker : public RBAContentSetMaker
{
public:
  RBASoundContentSetMaker();
  RBASoundContentSetMaker(const RBASoundContentSetMaker&)=delete;
  RBASoundContentSetMaker(const RBASoundContentSetMaker&&)=delete;
  RBASoundContentSetMaker& operator=(const RBASoundContentSetMaker&)=delete;
  RBASoundContentSetMaker& operator=(const RBASoundContentSetMaker&&)=delete;
  virtual ~RBASoundContentSetMaker()=default;

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

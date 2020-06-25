/// @file  RBASoundContentMaker.hpp
/// @brief SoundContentオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASOUNDCONTENTMAKER_HPP
#define RBASOUNDCONTENTMAKER_HPP

#include "RBAContentMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief SoundContentオブジェクト生成クラス
class RBASoundContentMaker : public RBAContentMaker
{
public:
  RBASoundContentMaker();
  RBASoundContentMaker(const RBASoundContentMaker&)=delete;
  RBASoundContentMaker(const RBASoundContentMaker&&)=delete;
  RBASoundContentMaker& operator=(const RBASoundContentMaker&)=delete;
  RBASoundContentMaker& operator=(const RBASoundContentMaker&&)=delete;
  virtual ~RBASoundContentMaker()=default;

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

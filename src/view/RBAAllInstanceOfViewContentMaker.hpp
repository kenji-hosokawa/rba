/// @file  RBAAllInstanceOfViewContentMaker.hpp
/// @brief AllInstanceOfViewContentオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLINSTANCEOFVIEWCONTENTMAKER_HPP
#define RBAALLINSTANCEOFVIEWCONTENTMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief AllInstanceOfViewContentオブジェクト生成クラス
class RBAAllInstanceOfViewContentMaker : public RBAExpressionMaker
{
public:
  RBAAllInstanceOfViewContentMaker();
  RBAAllInstanceOfViewContentMaker(const RBAAllInstanceOfViewContentMaker&)=delete;
  RBAAllInstanceOfViewContentMaker(const RBAAllInstanceOfViewContentMaker&&)=delete;
  RBAAllInstanceOfViewContentMaker& operator=(const RBAAllInstanceOfViewContentMaker&)=delete;
  RBAAllInstanceOfViewContentMaker& operator=(const RBAAllInstanceOfViewContentMaker&&)=delete;
  virtual ~RBAAllInstanceOfViewContentMaker()=default;

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

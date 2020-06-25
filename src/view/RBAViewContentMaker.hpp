/// @file  RBAViewContentMaker.hpp
/// @brief ViewContentオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAVIEWCONTENTMAKER_HPP
#define RBAVIEWCONTENTMAKER_HPP

#include "RBAContentMaker.hpp"

namespace rba
{

/// @brief ViewContentオブジェクト生成クラス
class RBAViewContentMaker : public RBAContentMaker
{
public:
  RBAViewContentMaker();
  RBAViewContentMaker(const RBAViewContentMaker&)=delete;
  RBAViewContentMaker(const RBAViewContentMaker&&)=delete;
  RBAViewContentMaker& operator=(const RBAViewContentMaker&)=delete;
  RBAViewContentMaker& operator=(const RBAViewContentMaker&&)=delete;
  virtual ~RBAViewContentMaker()=default;

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

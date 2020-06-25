/// @file  RBAViewContentSetMaker.hpp
/// @brief ViewContentSetオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAVIEWCONTENTSETMAKER_HPP
#define RBAVIEWCONTENTSETMAKER_HPP

#include "RBAContentSetMaker.hpp"

namespace rba
{

/// @brief ViewContentSetオブジェクト生成クラス
class RBAViewContentSetMaker : public RBAContentSetMaker
{
public:
  RBAViewContentSetMaker();
  RBAViewContentSetMaker(const RBAViewContentSetMaker&)=delete;
  RBAViewContentSetMaker(const RBAViewContentSetMaker&&)=delete;
  RBAViewContentSetMaker& operator=(const RBAViewContentSetMaker&)=delete;
  RBAViewContentSetMaker& operator=(const RBAViewContentSetMaker&&)=delete;
  virtual ~RBAViewContentSetMaker()=default;

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

/// @file  RBARuleObjectMaker.hpp
/// @brief ルールオプジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBARULEOBJECTMAKER_HPP
#define RBARULEOBJECTMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

/// @brief ルールオブジェクト生成クラス
class DLL_EXPORT RBARuleObjectMaker : public RBAModelElementMaker
{
public:
  explicit RBARuleObjectMaker(const std::string& label="");
  RBARuleObjectMaker(const RBARuleObjectMaker&)=delete;
  RBARuleObjectMaker(const RBARuleObjectMaker&&)=delete;
  RBARuleObjectMaker& operator=(const RBARuleObjectMaker&)=delete;
  RBARuleObjectMaker& operator=(const RBARuleObjectMaker&&)=delete;
  virtual ~RBARuleObjectMaker()=default;

protected:
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

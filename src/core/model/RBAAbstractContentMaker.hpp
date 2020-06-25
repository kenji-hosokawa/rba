/// @file  RBAAbstractContentMaker.hpp
/// @brief 抽象コンテント生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAABSTRACTCONTENTMAKER_HPP
#define RBAABSTRACTCONTENTMAKER_HPP

#include "RBARuleObjectMaker.hpp"

namespace rba
{

/// @brief 抽象アロケータブル生成クラス
class DLL_EXPORT RBAAbstractContentMaker : virtual public RBARuleObjectMaker
{
public:
  explicit RBAAbstractContentMaker(const std::string& label="");
  RBAAbstractContentMaker(const RBAAbstractContentMaker&)=delete;
  RBAAbstractContentMaker(const RBAAbstractContentMaker&&)=delete;
  RBAAbstractContentMaker& operator=(const RBAAbstractContentMaker&)=delete;
  RBAAbstractContentMaker& operator=(const RBAAbstractContentMaker&&)=delete;
  virtual ~RBAAbstractContentMaker()=default;

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

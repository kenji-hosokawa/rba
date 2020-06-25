/// @file  RBAContentMaker.hpp
/// @brief Contentオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACONTENTMAKER_HPP
#define RBACONTENTMAKER_HPP

#include "RBAAbstractContentMaker.hpp"

namespace rba
{

/// @brief Contentオブジェクト生成クラス
class DLL_EXPORT RBAContentMaker : public RBAAbstractContentMaker
{
public:
  explicit RBAContentMaker(const std::string& label="");
  RBAContentMaker(const RBAContentMaker&)=delete;
  RBAContentMaker(const RBAContentMaker&&)=delete;
  RBAContentMaker& operator=(const RBAContentMaker&)=delete;
  RBAContentMaker& operator=(const RBAContentMaker&&)=delete;
  virtual ~RBAContentMaker()=default;

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

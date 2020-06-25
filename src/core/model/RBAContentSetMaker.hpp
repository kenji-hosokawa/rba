/// @file  RBAContentSetMaker.hpp
/// @brief ContentSetオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACONTENTSETMAKER_HPP
#define RBACONTENTSETMAKER_HPP

#include "RBAAbstractContentMaker.hpp"

namespace rba
{

/// @brief ContentSetオブジェクト生成抽象クラス
class RBAContentSetMaker : public RBAAbstractContentMaker
{
public:
  explicit RBAContentSetMaker(const std::string& label="");
  RBAContentSetMaker(const RBAContentSetMaker&)=delete;
  RBAContentSetMaker(const RBAContentSetMaker&&)=delete;
  RBAContentSetMaker& operator=(const RBAContentSetMaker&)=delete;
  RBAContentSetMaker& operator=(const RBAContentSetMaker&&)=delete;
  virtual ~RBAContentSetMaker()=default;

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

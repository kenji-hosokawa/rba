/// @file  RBAAbstractConstraintMaker.hpp
/// @brief 抽象制約式オブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAABSTRACTCONSTRAINTMAKER_HPP
#define RBAABSTRACTCONSTRAINTMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

/// @brief 抽象制約式オブジェクト生成クラス
class DLL_EXPORT RBAAbstractConstraintMaker
  : public RBAModelElementMaker
{
public:
  explicit RBAAbstractConstraintMaker(const std::string& label);
  RBAAbstractConstraintMaker(const RBAAbstractConstraintMaker&)=delete;
  RBAAbstractConstraintMaker(const RBAAbstractConstraintMaker&&)=delete;
  RBAAbstractConstraintMaker& operator=(const RBAAbstractConstraintMaker&)=delete;
  RBAAbstractConstraintMaker& operator=(const RBAAbstractConstraintMaker&&)=delete;
  virtual ~RBAAbstractConstraintMaker()=default;

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

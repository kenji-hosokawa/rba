/// @file  RBAOperatorMaker.hpp
/// @brief Operatorオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAOPERATORMAKER_HPP
#define RBAOPERATORMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief Operatorオブジェクト生成抽象クラス
class DLL_EXPORT RBAOperatorMaker : public RBAExpressionMaker
{
public:
  explicit RBAOperatorMaker(const std::string& label="");
  RBAOperatorMaker(const RBAOperatorMaker&)=delete;
  RBAOperatorMaker(const RBAOperatorMaker&&)=delete;
  RBAOperatorMaker& operator=(const RBAOperatorMaker&)=delete;
  RBAOperatorMaker& operator=(const RBAOperatorMaker&&)=delete;
  virtual ~RBAOperatorMaker()=default;

protected:
  /// @brief 派生クラスごとにモデルエレメントの属性をセットする
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner) override;

};

}

#endif

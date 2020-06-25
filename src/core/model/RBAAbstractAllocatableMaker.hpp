/// @file  RBAAbstractAllocatableMaker.hpp
/// @brief 抽象アロケータブル生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAABSTRACTALLOCATABLEMAKER_HPP
#define RBAABSTRACTALLOCATABLEMAKER_HPP

#include "RBARuleObjectMaker.hpp"

namespace rba
{

/// @brief 抽象アロケータブル生成クラス
class DLL_EXPORT RBAAbstractAllocatableMaker : virtual public RBARuleObjectMaker
{
public:
  explicit RBAAbstractAllocatableMaker(const std::string& label="");
  RBAAbstractAllocatableMaker(const RBAAbstractAllocatableMaker&)=delete;
  RBAAbstractAllocatableMaker(const RBAAbstractAllocatableMaker&&)=delete;
  RBAAbstractAllocatableMaker& operator=(const RBAAbstractAllocatableMaker&)=delete;
  RBAAbstractAllocatableMaker& operator=(const RBAAbstractAllocatableMaker&&)=delete;
  virtual ~RBAAbstractAllocatableMaker()=default;

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

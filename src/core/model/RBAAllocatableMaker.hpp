/// @file  RBAAllocatableMaker.hpp
/// @brief Allocatableオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLOCATABLEMAKER_HPP
#define RBAALLOCATABLEMAKER_HPP

#include "RBAAbstractAllocatableMaker.hpp"

namespace rba
{

/// @brief Allocatableオブジェクト生成抽象クラス
class DLL_EXPORT RBAAllocatableMaker
  : public RBAAbstractAllocatableMaker
{
public:
  explicit RBAAllocatableMaker(const std::string& label="");
  RBAAllocatableMaker(const RBAAllocatableMaker&)=delete;
  RBAAllocatableMaker(const RBAAllocatableMaker&&)=delete;
  RBAAllocatableMaker& operator=(const RBAAllocatableMaker&)=delete;
  RBAAllocatableMaker& operator=(const RBAAllocatableMaker&&)=delete;
  virtual ~RBAAllocatableMaker()=default;

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

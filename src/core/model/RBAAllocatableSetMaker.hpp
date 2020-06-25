/// @file  RBAAllocatableSetMaker.hpp
/// @brief AllocatableSetオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLOCATABLESETMAKER_HPP
#define RBAALLOCATABLESETMAKER_HPP

#include "RBAAbstractAllocatableMaker.hpp"

namespace rba
{

/// @brief Allocatableオブジェクト生成抽象クラス
class RBAAllocatableSetMaker : public RBAAbstractAllocatableMaker
{
public:
  explicit RBAAllocatableSetMaker(const std::string& label="");
  RBAAllocatableSetMaker(const RBAAllocatableSetMaker&)=delete;
  RBAAllocatableSetMaker(const RBAAllocatableSetMaker&&)=delete;
  RBAAllocatableSetMaker& operator=(const RBAAllocatableSetMaker&)=delete;
  RBAAllocatableSetMaker& operator=(const RBAAllocatableSetMaker&&)=delete;
  virtual ~RBAAllocatableSetMaker()=default;

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

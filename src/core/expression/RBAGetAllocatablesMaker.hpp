/// @file  RBAGetAllocatablesMaker.hpp
/// @brief GetAllocatablesオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAGETALLOCATABLESMAKER_HPP
#define RBAGETALLOCATABLESMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief GetAllocatablesオブジェクト生成クラス
class RBAGetAllocatablesMaker : public RBAOperatorMaker
{
public:
  RBAGetAllocatablesMaker();
  RBAGetAllocatablesMaker(const RBAGetAllocatablesMaker&)=delete;
  RBAGetAllocatablesMaker(const RBAGetAllocatablesMaker&&)=delete;
  RBAGetAllocatablesMaker& operator=(const RBAGetAllocatablesMaker&)=delete;
  RBAGetAllocatablesMaker& operator=(const RBAGetAllocatablesMaker&&)=delete;
  virtual ~RBAGetAllocatablesMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

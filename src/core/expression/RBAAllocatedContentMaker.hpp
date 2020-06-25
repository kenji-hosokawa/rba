/// @file  RBAAllocatedContentMaker.hpp
/// @brief AllocatedContentオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLOCATEDCONTENTMAKER_HPP
#define RBAALLOCATEDCONTENTMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief AllocatedContentオブジェクト生成クラス
class RBAAllocatedContentMaker : public RBAOperatorMaker
{
public:
  RBAAllocatedContentMaker();
  RBAAllocatedContentMaker(const RBAAllocatedContentMaker&)=delete;
  RBAAllocatedContentMaker(const RBAAllocatedContentMaker&&)=delete;
  RBAAllocatedContentMaker& operator=(const RBAAllocatedContentMaker&)=delete;
  RBAAllocatedContentMaker& operator=(const RBAAllocatedContentMaker&&)=delete;
  virtual ~RBAAllocatedContentMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

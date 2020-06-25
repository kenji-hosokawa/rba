/// @file  RBAGetContentsListMaker.hpp
/// @brief GetContentsListオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAGETCONTENTSLISTMAKER_HPP
#define RBAGETCONTENTSLISTMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief GetContentsListオブジェクト生成クラス
class RBAGetContentsListMaker : public RBAOperatorMaker
{
public:
  RBAGetContentsListMaker();
  RBAGetContentsListMaker(const RBAGetContentsListMaker&)=delete;
  RBAGetContentsListMaker(const RBAGetContentsListMaker&&)=delete;
  RBAGetContentsListMaker& operator=(const RBAGetContentsListMaker&)=delete;
  RBAGetContentsListMaker& operator=(const RBAGetContentsListMaker&&)=delete;
  virtual ~RBAGetContentsListMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

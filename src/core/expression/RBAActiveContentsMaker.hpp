/// @file  RBAActiveContentsMaker.hpp
/// @brief ActiveContentsオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAACTIVECONTENTSMAKER_HPP
#define RBAACTIVECONTENTSMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ActiveContentsオブジェクト生成クラス
class RBAActiveContentsMaker : public RBAOperatorMaker
{
public:
  RBAActiveContentsMaker();
  RBAActiveContentsMaker(const RBAActiveContentsMaker&)=delete;
  RBAActiveContentsMaker(const RBAActiveContentsMaker&&)=delete;
  RBAActiveContentsMaker& operator=(const RBAActiveContentsMaker&)=delete;
  RBAActiveContentsMaker& operator=(const RBAActiveContentsMaker&&)=delete;
  virtual ~RBAActiveContentsMaker()=default;

public:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

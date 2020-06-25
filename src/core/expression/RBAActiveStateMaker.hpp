/// @file  RBAActiveStateMaker.hpp
/// @brief ActiveStateオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAACTIVESTATEMAKER_HPP
#define RBAACTIVESTATEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ActiveStateオブジェクト生成クラス
class RBAActiveStateMaker : public RBAOperatorMaker
{
public:
  RBAActiveStateMaker();
  RBAActiveStateMaker(const RBAActiveStateMaker&)=delete;
  RBAActiveStateMaker(const RBAActiveStateMaker&&)=delete;
  RBAActiveStateMaker& operator=(const RBAActiveStateMaker&)=delete;
  RBAActiveStateMaker& operator=(const RBAActiveStateMaker&&)=delete;
  virtual ~RBAActiveStateMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

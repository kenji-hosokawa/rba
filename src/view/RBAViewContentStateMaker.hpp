/// @file  RBAViewContentStateMaker.hpp
/// @brief ViewContentStateオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAVIEWCONTENTSTATEMAKER_HPP
#define RBAVIEWCONTENTSTATEMAKER_HPP

#include "RBAContentStateMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief ViewContentStateオブジェクト生成クラス
class RBAViewContentStateMaker : public RBAContentStateMaker
{
public:
  RBAViewContentStateMaker();
  RBAViewContentStateMaker(const RBAViewContentStateMaker&)=delete;
  RBAViewContentStateMaker(const RBAViewContentStateMaker&&)=delete;
  RBAViewContentStateMaker& operator=(const RBAViewContentStateMaker&)=delete;
  RBAViewContentStateMaker& operator=(RBAViewContentStateMaker&&)=delete;
  virtual ~RBAViewContentStateMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

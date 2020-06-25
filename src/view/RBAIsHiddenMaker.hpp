/// @file  RBAIsHiddenMaker.hpp
/// @brief IsHiddenオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISHIDDENMAKER_HPP
#define RBAISHIDDENMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsHiddenオブジェクト生成クラス
class RBAIsHiddenMaker : public RBAOperatorMaker
{
public:
  RBAIsHiddenMaker();
  RBAIsHiddenMaker(const RBAIsHiddenMaker&)=delete;
  RBAIsHiddenMaker(const RBAIsHiddenMaker&&)=delete;
  RBAIsHiddenMaker& operator=(const RBAIsHiddenMaker&)=delete;
  RBAIsHiddenMaker& operator=(const RBAIsHiddenMaker&&)=delete;
  virtual ~RBAIsHiddenMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

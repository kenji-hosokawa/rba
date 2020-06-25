/// @file  RBAIsSoundingMaker.hpp
/// @brief IsSoundingオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISSOUNDINGMAKER_HPP
#define RBAISSOUNDINGMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsSoundingオブジェクト生成クラス
class RBAIsSoundingMaker : public RBAOperatorMaker
{
public:
  RBAIsSoundingMaker();
  RBAIsSoundingMaker(const RBAIsSoundingMaker&)=delete;
  RBAIsSoundingMaker(const RBAIsSoundingMaker&&)=delete;
  RBAIsSoundingMaker& operator=(const RBAIsSoundingMaker&)=delete;
  RBAIsSoundingMaker& operator=(const RBAIsSoundingMaker&&)=delete;
  virtual ~RBAIsSoundingMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

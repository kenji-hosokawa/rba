/// @file  RBAIsGreaterThanEqualOperatorMaker.hpp
/// @brief IsGreaterThanEqualOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISGREATERTHANEQUALOPERATORMAKER_HPP
#define RBAISGREATERTHANEQUALOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsGreaterThanEqualOperatorオブジェクト生成クラス
class RBAIsGreaterThanEqualOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsGreaterThanEqualOperatorMaker();
  RBAIsGreaterThanEqualOperatorMaker(const RBAIsGreaterThanEqualOperatorMaker&)=delete;
  RBAIsGreaterThanEqualOperatorMaker(const RBAIsGreaterThanEqualOperatorMaker&&)=delete;
  RBAIsGreaterThanEqualOperatorMaker& operator=(const RBAIsGreaterThanEqualOperatorMaker&)=delete;
  RBAIsGreaterThanEqualOperatorMaker& operator=(const RBAIsGreaterThanEqualOperatorMaker&&)=delete;
  virtual ~RBAIsGreaterThanEqualOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

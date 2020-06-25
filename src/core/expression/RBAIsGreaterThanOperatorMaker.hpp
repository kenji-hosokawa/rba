/// @file  RBAIsGreaterThanEqualOperatorMaker.hpp
/// @brief IsGreaterThanEqualOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISGREATERTHANOPERATORMAKER_HPP
#define RBAISGREATERTHANOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsGreaterThanOperatorオブジェクト生成クラス
class RBAIsGreaterThanOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsGreaterThanOperatorMaker();
  RBAIsGreaterThanOperatorMaker(const RBAIsGreaterThanOperatorMaker&)=delete;
  RBAIsGreaterThanOperatorMaker(const RBAIsGreaterThanOperatorMaker&&)=delete;
  RBAIsGreaterThanOperatorMaker& operator=(const RBAIsGreaterThanOperatorMaker&)=delete;
  RBAIsGreaterThanOperatorMaker& operator=(const RBAIsGreaterThanOperatorMaker&&)=delete;
  virtual ~RBAIsGreaterThanOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

/// @file  RBAIsLowerThanEqualOperatorMaker.hpp
/// @brief IsLowerThanEqualOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISLOWERTHANEQUALOPERATORMAKER_HPP
#define RBAISLOWERTHANEQUALOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsLowerThanEqualOperatorオブジェクト生成クラス
class RBAIsLowerThanEqualOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsLowerThanEqualOperatorMaker();
  RBAIsLowerThanEqualOperatorMaker(const RBAIsLowerThanEqualOperatorMaker&)=delete;
  RBAIsLowerThanEqualOperatorMaker(const RBAIsLowerThanEqualOperatorMaker&&)=delete;
  RBAIsLowerThanEqualOperatorMaker& operator=(const RBAIsLowerThanEqualOperatorMaker&)=delete;
  RBAIsLowerThanEqualOperatorMaker& operator=(const RBAIsLowerThanEqualOperatorMaker&&)=delete;
  virtual ~RBAIsLowerThanEqualOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

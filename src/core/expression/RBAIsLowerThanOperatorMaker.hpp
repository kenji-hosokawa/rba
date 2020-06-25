/// @file  RBAIsLowerThanOperatorMaker.hpp
/// @brief IsLowerThanOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISLOWERTHANOPERATORMAKER_HPP
#define RBAISLOWERTHANOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsLowerThanOperatorオブジェクト生成クラス
class RBAIsLowerThanOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsLowerThanOperatorMaker();
  RBAIsLowerThanOperatorMaker(const RBAIsLowerThanOperatorMaker&)=delete;
  RBAIsLowerThanOperatorMaker(const RBAIsLowerThanOperatorMaker&&)=delete;
  RBAIsLowerThanOperatorMaker& operator=(const RBAIsLowerThanOperatorMaker&)=delete;
  RBAIsLowerThanOperatorMaker& operator=(const RBAIsLowerThanOperatorMaker&&)=delete;
  virtual ~RBAIsLowerThanOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

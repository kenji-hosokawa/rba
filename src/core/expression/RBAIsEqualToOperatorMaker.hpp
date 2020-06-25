/// @file  RBAIsEqualToOperatorMaker.hpp
/// @brief IsEqualToOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISEQUALTOOPERATORMAKER_HPP
#define RBAISEQUALTOOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsEqualToOperatorオブジェクト生成クラス
class RBAIsEqualToOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsEqualToOperatorMaker();
  RBAIsEqualToOperatorMaker(const RBAIsEqualToOperatorMaker&)=delete;
  RBAIsEqualToOperatorMaker(const RBAIsEqualToOperatorMaker&&)=delete;
  RBAIsEqualToOperatorMaker& operator=(const RBAIsEqualToOperatorMaker&)=delete;
  RBAIsEqualToOperatorMaker& operator=(const RBAIsEqualToOperatorMaker&&)=delete;
  virtual ~RBAIsEqualToOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

/// @file  RBAImpliesOperatorMaker.hpp
/// @brief ImpliesOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAIMPLIEDOPERATORMAKER_HPP
#define RBAIMPLIEDOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ImpliesOperatorオブジェクト生成クラス
class RBAImpliesOperatorMaker : public RBAOperatorMaker
{
public:
  RBAImpliesOperatorMaker();
  RBAImpliesOperatorMaker(const RBAImpliesOperatorMaker&)=delete;
  RBAImpliesOperatorMaker(const RBAImpliesOperatorMaker&&)=delete;
  RBAImpliesOperatorMaker& operator=(const RBAImpliesOperatorMaker&)=delete;
  RBAImpliesOperatorMaker& operator=(const RBAImpliesOperatorMaker&&)=delete;
  virtual ~RBAImpliesOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

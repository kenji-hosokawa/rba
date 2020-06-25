/// @file  RBAAndOperatorMaker.hpp
/// @brief AndOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAANDOPERATORMAKER_HPP
#define RBAANDOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief AndOperatorオブジェクト生成クラス
class RBAAndOperatorMaker : public RBAOperatorMaker
{
public:
  RBAAndOperatorMaker();
  RBAAndOperatorMaker(const RBAAndOperatorMaker&)=delete;
  RBAAndOperatorMaker(const RBAAndOperatorMaker&&)=delete;
  RBAAndOperatorMaker& operator=(const RBAAndOperatorMaker&)=delete;
  RBAAndOperatorMaker& operator=(const RBAAndOperatorMaker&&)=delete;
  virtual ~RBAAndOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

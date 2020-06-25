/// @file  RBASizeOperatorMaker.hpp
/// @brief SizeOperatorオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASIZEOPERATORMAKER_HPP
#define RBASIZEOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief SizeOperatorオブジェクト生成クラス
class RBASizeOperatorMaker : public RBAOperatorMaker
{
public:
  RBASizeOperatorMaker();
  RBASizeOperatorMaker(const RBASizeOperatorMaker&)=delete;
  RBASizeOperatorMaker(const RBASizeOperatorMaker&&)=delete;
  RBASizeOperatorMaker& operator=(const RBASizeOperatorMaker&)=delete;
  RBASizeOperatorMaker& operator=(const RBASizeOperatorMaker&&)=delete;
  virtual ~RBASizeOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

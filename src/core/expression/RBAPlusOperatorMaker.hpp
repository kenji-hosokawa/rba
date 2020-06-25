/// @file  RBAPlusOperatorsMaker.hpp
/// @brief PlusOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAPLUSOPERATORMAKER_HPP
#define RBAPLUSOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief PlusOperatorオブジェクト生成クラス
class RBAPlusOperatorMaker : public RBAOperatorMaker
{
public:
  RBAPlusOperatorMaker();
  RBAPlusOperatorMaker(const RBAPlusOperatorMaker&)=delete;
  RBAPlusOperatorMaker(const RBAPlusOperatorMaker&&)=delete;
  RBAPlusOperatorMaker& operator=(const RBAPlusOperatorMaker&)=delete;
  RBAPlusOperatorMaker& operator=(const RBAPlusOperatorMaker&&)=delete;
  virtual ~RBAPlusOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

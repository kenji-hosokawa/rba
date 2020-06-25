/// @file  RBANotOperatorMaker.hpp
/// @brief NotOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBANOTOPERATORMAKER_HPP
#define RBANOTOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief NotOperatorオブジェクト生成クラス
class RBANotOperatorMaker : public RBAOperatorMaker
{
public:
  RBANotOperatorMaker();
  RBANotOperatorMaker(const RBANotOperatorMaker&)=delete;
  RBANotOperatorMaker(const RBANotOperatorMaker&&)=delete;
  RBANotOperatorMaker& operator=(const RBANotOperatorMaker&)=delete;
  RBANotOperatorMaker& operator=(const RBANotOperatorMaker&&)=delete;
  virtual ~RBANotOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

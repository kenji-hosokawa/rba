/// @file  RBAOrOperatorMaker.hpp
/// @brief OrOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAOROPERATORMAKER_HPP
#define RBAOROPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief OrOperatorオブジェクト生成クラス
class RBAOrOperatorMaker : public RBAOperatorMaker
{
public:
  RBAOrOperatorMaker();
  RBAOrOperatorMaker(const RBAOrOperatorMaker&)=delete;
  RBAOrOperatorMaker(const RBAOrOperatorMaker&&)=delete;
  RBAOrOperatorMaker& operator=(const RBAOrOperatorMaker&)=delete;
  RBAOrOperatorMaker& operator=(const RBAOrOperatorMaker&&)=delete;
  virtual ~RBAOrOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

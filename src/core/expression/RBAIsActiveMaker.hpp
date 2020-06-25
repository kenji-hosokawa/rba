/// @file  RBAIsActiveMaker.hpp
/// @brief IsActiveオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISACTIVEMAKER_HPP
#define RBAISACTIVEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsActiveオブジェクト生成クラス
class RBAIsActiveMaker : public RBAOperatorMaker
{
public:
  RBAIsActiveMaker();
  RBAIsActiveMaker(const RBAIsActiveMaker&)=delete;
  RBAIsActiveMaker(const RBAIsActiveMaker&&)=delete;
  RBAIsActiveMaker& operator=(const RBAIsActiveMaker&)=delete;
  RBAIsActiveMaker& operator=(const RBAIsActiveMaker&&)=delete;
  virtual ~RBAIsActiveMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

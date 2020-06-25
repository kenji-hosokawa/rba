/// @file  RBAGetPropertyMaker.hpp
/// @brief GetPropertyオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAGETPROPERTYMAKER_HPP
#define RBAGETPROPERTYMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief GetPropertyオブジェクト生成クラス
class RBAGetPropertyMaker : public RBAOperatorMaker
{
public:
  RBAGetPropertyMaker();
  RBAGetPropertyMaker(const RBAGetPropertyMaker&)=delete;
  RBAGetPropertyMaker(const RBAGetPropertyMaker&&)=delete;
  RBAGetPropertyMaker& operator=(const RBAGetPropertyMaker&)=delete;
  RBAGetPropertyMaker& operator=(const RBAGetPropertyMaker&&)=delete;
  virtual ~RBAGetPropertyMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

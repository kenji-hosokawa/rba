/// @file  RBAIsVisibleMaker.hpp
/// @brief IsVisibleオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISVISIBLEMAKER_HPP
#define RBAISVISIBLEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsVisibleオブジェクト生成クラス
class RBAIsVisibleMaker : public RBAOperatorMaker
{
public:
  RBAIsVisibleMaker();
  RBAIsVisibleMaker(const RBAIsVisibleMaker&)=delete;
  RBAIsVisibleMaker(const RBAIsVisibleMaker&&)=delete;
  RBAIsVisibleMaker& operator=(const RBAIsVisibleMaker&)=delete;
  RBAIsVisibleMaker& operator=(const RBAIsVisibleMaker&&)=delete;
  virtual ~RBAIsVisibleMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

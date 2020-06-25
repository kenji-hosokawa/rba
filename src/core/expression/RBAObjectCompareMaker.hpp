/// @file  RBAObjectCompareMaker.hpp
/// @brief ObjectCompareオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAOBJECTCOMPAREMAKER_HPP
#define RBAOBJECTCOMPAREMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ObjectCompareオブジェクト生成クラス
class RBAObjectCompareMaker : public RBAOperatorMaker
{
public:
  RBAObjectCompareMaker();
  RBAObjectCompareMaker(const RBAObjectCompareMaker&)=delete;
  RBAObjectCompareMaker(const RBAObjectCompareMaker&&)=delete;
  RBAObjectCompareMaker& operator=(const RBAObjectCompareMaker&)=delete;
  RBAObjectCompareMaker& operator=(const RBAObjectCompareMaker&&)=delete;
  virtual ~RBAObjectCompareMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

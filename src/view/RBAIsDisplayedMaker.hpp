/// @file  RBAIsDisplayedMaker.hpp
/// @brief IsDisplayedオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISDISPLAYEDMAKER_HPP
#define RBAISDISPLAYEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsDisplayedオブジェクト生成クラス
class RBAIsDisplayedMaker : public RBAOperatorMaker
{
public:
  RBAIsDisplayedMaker();
  RBAIsDisplayedMaker(const RBAIsDisplayedMaker&)=delete;
  RBAIsDisplayedMaker(const RBAIsDisplayedMaker&&)=delete;
  RBAIsDisplayedMaker& operator=(const RBAIsDisplayedMaker&)=delete;
  RBAIsDisplayedMaker& operator=(const RBAIsDisplayedMaker&&)=delete;
  virtual ~RBAIsDisplayedMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

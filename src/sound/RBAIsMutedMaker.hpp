/// @file  RBAIsMutedMaker.hpp
/// @brief IsMutedオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISMUTEDMAKER_HPP
#define RBAISMUTEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsMutedオブジェクト生成クラス
class RBAIsMutedMaker : public RBAOperatorMaker
{
public:
  RBAIsMutedMaker();
  RBAIsMutedMaker(const RBAIsMutedMaker&)=delete;
  RBAIsMutedMaker(const RBAIsMutedMaker&&)=delete;
  RBAIsMutedMaker& operator=(const RBAIsMutedMaker&)=delete;
  RBAIsMutedMaker& operator=(const RBAIsMutedMaker&&)=delete;
  virtual ~RBAIsMutedMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

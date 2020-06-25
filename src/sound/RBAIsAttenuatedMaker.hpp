/// @file  RBAIsAttenuatedMaker.hpp
/// @brief IsAttenuatedオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISATTENUATEDMAKER_HPP
#define RBAISATTENUATEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsAttenuatedオブジェクト生成クラス
class RBAIsAttenuatedMaker : public RBAOperatorMaker
{
public:
  RBAIsAttenuatedMaker();
  RBAIsAttenuatedMaker(const RBAIsAttenuatedMaker&)=delete;
  RBAIsAttenuatedMaker(const RBAIsAttenuatedMaker&&)=delete;
  RBAIsAttenuatedMaker& operator=(const RBAIsAttenuatedMaker&)=delete;
  RBAIsAttenuatedMaker& operator=(const RBAIsAttenuatedMaker&&)=delete;
  virtual ~RBAIsAttenuatedMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

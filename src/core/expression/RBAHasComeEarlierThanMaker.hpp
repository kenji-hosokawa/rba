/// @file  RBAHasComeEarlierThanMaker.hpp
/// @brief オブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAHASCOMEEARLIERTHANMAKER_HPP
#define RBAHASCOMEEARLIERTHANMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief HasComeEarlierThanオブジェクト生成クラス
class RBAHasComeEarlierThanMaker : public RBAOperatorMaker
{
public:
  RBAHasComeEarlierThanMaker();
  RBAHasComeEarlierThanMaker(const RBAHasComeEarlierThanMaker&)=delete;
  RBAHasComeEarlierThanMaker(const RBAHasComeEarlierThanMaker&&)=delete;
  RBAHasComeEarlierThanMaker& operator=(const RBAHasComeEarlierThanMaker&)=delete;
  RBAHasComeEarlierThanMaker& operator=(const RBAHasComeEarlierThanMaker&&)=delete;
  virtual ~RBAHasComeEarlierThanMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

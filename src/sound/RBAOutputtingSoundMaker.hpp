/// @file  RBAOutputtingSoundMaker.hpp
/// @brief OutputtingSoundオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAOUTPUTTINGSOUNDMAKER_HPP
#define RBAOUTPUTTINGSOUNDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief OutputtingSoundオブジェクト生成クラス
class RBAOutputtingSoundMaker : public RBAOperatorMaker
{
public:
  RBAOutputtingSoundMaker();
  RBAOutputtingSoundMaker(const RBAOutputtingSoundMaker&)=delete;
  RBAOutputtingSoundMaker(const RBAOutputtingSoundMaker&&)=delete;
  RBAOutputtingSoundMaker& operator=(const RBAOutputtingSoundMaker&)=delete;
  RBAOutputtingSoundMaker& operator=(const RBAOutputtingSoundMaker&&)=delete;
  virtual ~RBAOutputtingSoundMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

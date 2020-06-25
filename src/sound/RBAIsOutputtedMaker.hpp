/// @file  RBAIsOutputtedMaker.hpp
/// @brief IsOutputtedオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISOUTPUTTEDMAKER_HPP
#define RBAISOUTPUTTEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsOutputtedオブジェクト生成クラス
class RBAIsOutputtedMaker : public RBAOperatorMaker
{
public:
  RBAIsOutputtedMaker();
  RBAIsOutputtedMaker(const RBAIsOutputtedMaker&)=delete;
  RBAIsOutputtedMaker(const RBAIsOutputtedMaker&&)=delete;
  RBAIsOutputtedMaker& operator=(const RBAIsOutputtedMaker&)=delete;
  RBAIsOutputtedMaker& operator=(const RBAIsOutputtedMaker&&)=delete;
  virtual ~RBAIsOutputtedMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

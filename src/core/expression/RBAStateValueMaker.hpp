/// @file  RBAStateValueMaker.hpp
/// @brief StateValueオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASTATEVALUEMAKER_HPP
#define RBASTATEVALUEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief StateValueオブジェクト生成クラス
class RBAStateValueMaker : public RBAOperatorMaker
{
public:
  RBAStateValueMaker();
  RBAStateValueMaker(const RBAStateValueMaker&)=delete;
  RBAStateValueMaker(const RBAStateValueMaker&&)=delete;
  RBAStateValueMaker& operator=(const RBAStateValueMaker&)=delete;
  RBAStateValueMaker& operator=(const RBAStateValueMaker&&)=delete;
  virtual ~RBAStateValueMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

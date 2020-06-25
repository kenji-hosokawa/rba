/// @file  RBAContentValueMaker.hpp
/// @brief ContentValueオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACONTENTVALUEMAKER_HPP
#define RBACONTENTVALUEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ContentValueオブジェクト生成クラス
class RBAContentValueMaker : public RBAOperatorMaker
{
public:
  RBAContentValueMaker();
  RBAContentValueMaker(const RBAContentValueMaker&)=delete;
  RBAContentValueMaker(const RBAContentValueMaker&&)=delete;
  RBAContentValueMaker& operator=(const RBAContentValueMaker&)=delete;
  RBAContentValueMaker& operator=(const RBAContentValueMaker&&)=delete;
  virtual ~RBAContentValueMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

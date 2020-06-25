/// @file  RBASetOfOperatorMaker.hpp
/// @brief SetOfOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASETOFOPERATORMAKER_HPP
#define RBASETOFOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief SetOfOperatorオブジェクト生成クラス
class RBASetOfOperatorMaker : public RBAOperatorMaker
{
public:
  RBASetOfOperatorMaker();
  RBASetOfOperatorMaker(const RBASetOfOperatorMaker&)=delete;
  RBASetOfOperatorMaker(const RBASetOfOperatorMaker&&)=delete;
  RBASetOfOperatorMaker& operator=(const RBASetOfOperatorMaker&)=delete;
  RBASetOfOperatorMaker& operator=(const RBASetOfOperatorMaker&&)=delete;
  virtual ~RBASetOfOperatorMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

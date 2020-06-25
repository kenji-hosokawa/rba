/// @file  RBAHasComeLaterThanMaker.hpp
/// @brief HasComeLaterThanオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAHASCOMELATERTHANMAKER_HPP
#define RBAHASCOMELATERTHANMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief HasComeLaterThanオブジェクト生成クラス
class RBAHasComeLaterThanMaker : public RBAOperatorMaker
{
public:
  RBAHasComeLaterThanMaker();
  RBAHasComeLaterThanMaker(const RBAHasComeLaterThanMaker&)=delete;
  RBAHasComeLaterThanMaker(const RBAHasComeLaterThanMaker&&)=delete;
  RBAHasComeLaterThanMaker& operator=(const RBAHasComeLaterThanMaker&)=delete;
  RBAHasComeLaterThanMaker& operator=(const RBAHasComeLaterThanMaker&&)=delete;
  virtual ~RBAHasComeLaterThanMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

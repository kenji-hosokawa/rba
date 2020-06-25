/// @file  RBAHasBeenDisplayedMaker.hpp
/// @brief HasBeenDisplayedオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAHASBEENDISPLAYEDMAKER_HPP
#define RBAHASBEENDISPLAYEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief HasBeenDisplayedオブジェクト生成クラス
class RBAHasBeenDisplayedMaker : public RBAOperatorMaker
{
public:
  RBAHasBeenDisplayedMaker();
  RBAHasBeenDisplayedMaker(const RBAHasBeenDisplayedMaker&)=delete;
  RBAHasBeenDisplayedMaker(const RBAHasBeenDisplayedMaker&&)=delete;
  RBAHasBeenDisplayedMaker& operator=(const RBAHasBeenDisplayedMaker&)=delete;
  RBAHasBeenDisplayedMaker& operator=(const RBAHasBeenDisplayedMaker&&)=delete;
  virtual ~RBAHasBeenDisplayedMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

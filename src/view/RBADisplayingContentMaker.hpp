/// @file  RBADisplayingContentMaker.hpp
/// @brief DisplayingContentオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBADISPLAYINGCONTENTMAKER_HPP
#define RBADISPLAYINGCONTENTMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief DisplayingContentオブジェクト生成クラス
class RBADisplayingContentMaker : public RBAOperatorMaker
{
public:
  RBADisplayingContentMaker();
  RBADisplayingContentMaker(const RBADisplayingContentMaker&)=delete;
  RBADisplayingContentMaker(const RBADisplayingContentMaker&&)=delete;
  RBADisplayingContentMaker& operator=(const RBADisplayingContentMaker&)=delete;
  RBADisplayingContentMaker& operator=(const RBADisplayingContentMaker&&)=delete;
  virtual ~RBADisplayingContentMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif

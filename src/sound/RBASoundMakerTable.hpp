/// @file  RBASoundMakerTable.hpp
/// @brief 音声エレメントメーカーテーブルクラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASOUNDMAKERTABLE_HPP
#define RBASOUNDMAKERTABLE_HPP

#include <functional>
#include "RBAAbstractMakerTable.hpp"

namespace rba
{

class DLL_EXPORT RBASoundMakerTable : public RBAAbstractMakerTable
{
public:
  RBASoundMakerTable();
  RBASoundMakerTable(const RBASoundMakerTable&)=delete;
  RBASoundMakerTable(const RBASoundMakerTable&&)=delete;
  RBASoundMakerTable& operator=(const RBASoundMakerTable&)=delete;
  RBASoundMakerTable& operator=(const RBASoundMakerTable&&)=delete;
  virtual ~RBASoundMakerTable()=default;

public:
  std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const override;

};

}

#endif

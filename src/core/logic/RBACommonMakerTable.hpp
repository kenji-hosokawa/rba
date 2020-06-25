/// @file  RBACommonMakerTable.hpp
/// @brief 共通エレメントメーカーテーブルクラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACOMMONMAKERTABLE_HPP
#define RBACOMMONMAKERTABLE_HPP

#include "RBAAbstractMakerTable.hpp"

namespace rba
{

class DLL_EXPORT RBACommonMakerTable : public RBAAbstractMakerTable
{
public:
  RBACommonMakerTable();
  RBACommonMakerTable(const RBACommonMakerTable&)=delete;
  RBACommonMakerTable(const RBACommonMakerTable&&)=delete;
  RBACommonMakerTable& operator=(const RBACommonMakerTable&)=delete;
  RBACommonMakerTable& operator=(const RBACommonMakerTable&&)=delete;
  virtual ~RBACommonMakerTable()=default;

public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const override;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

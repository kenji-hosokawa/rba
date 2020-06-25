/// @file  RBAViewMakerTable.hpp
/// @brief ビューエレメントメーカーテーブルクラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAVIEWMAKERTABLE_HPP
#define RBAVIEWMAKERTABLE_HPP

#include <functional>
#include "RBAAbstractMakerTable.hpp"

namespace rba
{

class DLL_EXPORT RBAViewMakerTable : public RBAAbstractMakerTable
{
public:
  RBAViewMakerTable();
  RBAViewMakerTable(const RBAViewMakerTable&)=delete;
  RBAViewMakerTable(const RBAViewMakerTable&&)=delete;
  RBAViewMakerTable& operator=(const RBAViewMakerTable&)=delete;
  RBAViewMakerTable& operator=(const RBAViewMakerTable&&)=delete;
  virtual ~RBAViewMakerTable()=default;

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

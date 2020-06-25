/// @file  RBAAbstractMakerTable.hpp
/// @brief メーカーテーブル抽象化クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAABSTRACTMAKERTABLE_HPP
#define RBAABSTRACTMAKERTABLE_HPP

#include <memory>
#include "RBAModelElementMaker.hpp"

namespace rba
{

class DLL_EXPORT RBAAbstractMakerTable
{
public:
  RBAAbstractMakerTable()=default;
  RBAAbstractMakerTable(const RBAAbstractMakerTable&)=delete;
  RBAAbstractMakerTable(const RBAAbstractMakerTable&&)=delete;
  RBAAbstractMakerTable& operator=(const RBAAbstractMakerTable&)=delete;
  RBAAbstractMakerTable& operator=(const RBAAbstractMakerTable&&)=delete;
  virtual ~RBAAbstractMakerTable()=default;

public:
  virtual std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const=0;
  virtual const std::list<std::string>& getTags() const;

protected:
  void addTag(const std::string& tag);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<std::string> tags_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

/// @file  RBAAbstractMakerTable.cpp
/// @brief メーカーテーブル抽象化クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAbstractMakerTable.hpp"

namespace rba
{

const std::list<std::string>&
RBAAbstractMakerTable::getTags() const
{
  return tags_;
}

void
RBAAbstractMakerTable::addTag(const std::string& tag)
{
  tags_.push_back(tag);
}

}


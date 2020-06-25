/// @file  RBAJsonParser.cpp
/// @brief JSONパーサークラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAJsonParser.hpp"
#include "RBAJsonParserImpl.hpp"
#include "RBAExpression.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAJsonParser::RBAJsonParser()
  : impl_{std::make_unique<RBAJsonParser::Impl>()}
{
};

RBAJsonParser::RBAJsonParser(RBAModelFactory* factory)
  : impl_{std::make_unique<RBAJsonParser::Impl>(factory)}
{
};

RBAJsonParser::~RBAJsonParser() noexcept
{
};

RBAModel*
RBAJsonParser::parse(const std::string& filename)
{
  return impl_->parse(filename);
}

}

/// @file  RBAJsonParserImpl.hpp
/// @brief JSONパーサー実装クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAJSONPARSERIMPL_HPP
#define RBAJSONPARSERIMPL_HPP

#include <mutex>
#include "RBAJsonParser.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

class RBAJsonElement;
enum class RBAConstraintMap : std::uint8_t;

/// @brief JSONパーサー実装クラス
class RBAJsonParser::Impl
{
public:
  Impl(RBAModelFactory* const factory=nullptr);
  Impl(const Impl&)=delete;
  Impl(const Impl&&)=delete;
  Impl& operator=(const Impl&)=delete;
  Impl& operator=(const Impl&&)=delete;
  virtual ~Impl()=default;

public:
  RBAModel* parse(const std::string& filename);

private:
  virtual void resetFactory();

private:
  void createConstraintMap(const RBAJsonElement* const constraints,
                           const RBAConstraintMap& kind);
  void createAllocatablesMap(const RBAJsonElement* const allocMap);
  std::unique_ptr<RBAJsonElement> readJsonFile(const std::string& filename);
  std::unique_ptr<RBAJsonElement> readJsonString(const std::string& jsonstring);

private:
  enum class Status : std::uint8_t {
    START,
    VALUE,
  };
  RBAModelFactory* orgFactory_;
  RBAModelFactory* factory_;
  std::unique_ptr<RBAModelFactory> uniqueFactory_;
  std::mutex mutex_;
};

}

#endif

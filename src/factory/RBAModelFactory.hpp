/// @file  RBAModelFactory.hpp
/// @brief モデルファクトリクラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAMODELFACTORY_HPP
#define RBAMODELFACTORY_HPP

#include <string>
#include <list>
#include <memory>
#include <unordered_map>
#include "RBADllExport.hpp"

namespace rba
{

class RBAModel;
class RBAModelImpl;
class RBAJsonElement;
class RBAModelElement;
class RBAVariable;
class RBAAbstractMakerTable;
class RBAModelElementMaker;
enum class RBAConstraintMap : std::uint8_t;

/// @brief モデルファクトリクラス
class DLL_EXPORT RBAModelFactory
{
public:
  RBAModelFactory(RBAModelImpl* const model=nullptr);
  RBAModelFactory(const RBAModelFactory&)=delete;
  RBAModelFactory(const RBAModelFactory&&)=delete;
  RBAModelFactory& operator=(const RBAModelFactory&)=delete;
  RBAModelFactory& operator=(const RBAModelFactory&&)=delete;
  virtual ~RBAModelFactory() noexcept;

 public:
  RBAModel* const getModel() const;
  void deleteModel();
  void addMakerTable(const RBAAbstractMakerTable& makerTable);
  void addMaker(const std::string label,
                std::unique_ptr<RBAModelElementMaker> maker);
  bool hasMaker() const;
  const std::list<std::string>& getTags() const;

  RBAModelElement* createElement(const std::string& className,
                                 const RBAJsonElement* const jsonElement,
                                 RBAModelElement* const owner=nullptr);

  void setAllocatableConstraint(const std::string& allocatableName,
                                const std::string& constraintName,
                                const RBAConstraintMap& kind);

  void pushVariable(const RBAVariable* const var);
  void popVariable();
  const RBAVariable* getVariable(const std::string& varName);

  void resetException();
  void setException();
  bool isException() const;

private:
  RBAModelImpl* model_;
  bool exception_;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unordered_map<std::string, RBAModelElementMaker*> nameToMaker_;
  // 保存用unique_ptrリスト
  std::list<std::unique_ptr<RBAModelElementMaker>> makers_;
  // 作業用のカレント変数
  std::list<const RBAVariable*> currentVariables_;
  // JSONエレメントのタグ一覧、登録したMakerTableからセット
  std::list<std::string> tags_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

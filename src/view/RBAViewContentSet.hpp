/**
 * 表示コンテントセットクラスヘッダファイル
 */

#ifndef RBAVIEWCONTENTSET_HPP
#define RBAVIEWCONTENTSET_HPP

#include "RBAContentSet.hpp"
#include "RBADllExport.hpp"

namespace rba
{

class RBAViewContent;
class RBAViewContentImpl;

class DLL_EXPORT RBAViewContentSet : public RBAContentSet
{
public:
  explicit RBAViewContentSet(const std::string& name="");
  RBAViewContentSet(const RBAViewContentSet&)=delete;
  RBAViewContentSet(const RBAViewContentSet&&)=delete;
  RBAViewContentSet& operator=(const RBAViewContentSet&)=delete;
  RBAViewContentSet& operator=(const RBAViewContentSet&&)=delete;
  virtual ~RBAViewContentSet()=default;

public:
  const std::list<const RBAViewContent*>& getTargets() const;
  void addTarget(const RBAContent* content) override;
  void clear() override;
  RBAModelElementType getModelElementType() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAViewContent*> externalContents_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

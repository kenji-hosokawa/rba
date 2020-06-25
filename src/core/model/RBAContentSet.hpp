/**
 * コンテントセットクラス
 */

#ifndef RBACONTENTSET_HPP
#define RBACONTENTSET_HPP

#include <list>
#include "RBAAbstractContent.hpp"

namespace rba
{

class RBAContent;

class DLL_EXPORT RBAContentSet : public RBAAbstractContent
{
public:
  explicit RBAContentSet(const std::string& name="");
  RBAContentSet(const RBAContentSet&)=delete;
  RBAContentSet(const RBAContentSet&&)=delete;
  RBAContentSet& operator=(const RBAContentSet&)=delete;
  RBAContentSet& operator=(const RBAContentSet&&)=delete;
  virtual ~RBAContentSet()=default;

public:
  virtual void addTarget(const RBAContent* content);
  virtual void clear();
  const std::list<const RBAContent*>& getLeafContent() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAContent*> leafContent_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

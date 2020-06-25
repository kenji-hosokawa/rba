/**
 * 抽象アロケータブルクラスヘッダファイル
 */

#ifndef RBAABSTRACTALLOCATABLE_HPP
#define RBAABSTRACTALLOCATABLE_HPP

#include <memory>
#include <list>
#include "RBARuleObject.hpp"
#include "RBAContentSet.hpp"

namespace rba
{

class RBAContent;

class DLL_EXPORT RBAAbstractAllocatable : virtual public RBARuleObject
{
protected:
  explicit RBAAbstractAllocatable(const std::string& name="");
  RBAAbstractAllocatable(const RBAAbstractAllocatable&)=delete;
  RBAAbstractAllocatable(const RBAAbstractAllocatable&&)=delete;
  RBAAbstractAllocatable& operator=(const RBAAbstractAllocatable&)=delete;
  RBAAbstractAllocatable& operator=(const RBAAbstractAllocatable&&)=delete;

public:
  virtual ~RBAAbstractAllocatable()=default;

public:
  const std::list<const RBAContent*>& getInternalContents() const;
  void addContent(const RBAContent* const content);
  const RBAContentSet* getContentSet() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAContentSet> contentSet_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

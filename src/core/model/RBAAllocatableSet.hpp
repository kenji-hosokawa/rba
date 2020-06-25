/**
 * アロケータブルセットクラス
 */

#ifndef RBAALLOCATABLESET_HPP
#define RBAALLOCATABLESET_HPP

#include "RBAAbstractAllocatable.hpp"

namespace rba
{

class RBAAllocatable;

class DLL_EXPORT RBAAllocatableSet : public RBAAbstractAllocatable
{
public:
  explicit RBAAllocatableSet(const std::string& name="");
  RBAAllocatableSet(const RBAAllocatableSet&)=delete;
  RBAAllocatableSet(const RBAAllocatableSet&&)=delete;
  RBAAllocatableSet& operator=(const RBAAllocatableSet&)=delete;
  RBAAllocatableSet& operator=(const RBAAllocatableSet&&)=delete;
  virtual ~RBAAllocatableSet()=default;

public:
  virtual void addTarget(const RBAAllocatable* alloc);
  virtual void clear();
  const std::list<const RBAAllocatable*>& getLeafAllocatable() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAAllocatable*> leafAllocatable_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}
#endif

/**
 * ゾーンセットクラスヘッダファイル
 */

#ifndef RBAZONESET_HPP
#define RBAZONESET_HPP

#include "RBAAllocatableSet.hpp"

namespace rba
{

class RBAZoneImpl;
class RBAZone;

class DLL_EXPORT RBAZoneSet : public RBAAllocatableSet
{
public:
  explicit RBAZoneSet(const std::string& name="");
  RBAZoneSet(const RBAZoneSet&)=delete;
  RBAZoneSet(const RBAZoneSet&&)=delete;
  RBAZoneSet& operator=(const RBAZoneSet&)=delete;
  RBAZoneSet& operator=(const RBAZoneSet&&)=delete;
  virtual ~RBAZoneSet()=default;

public:
  const std::list<const RBAZone*>& getTargets() const;
  void addTarget(const RBAAllocatable* alloc) override;
  void clear() override;
  RBAModelElementType getModelElementType() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAZone*> externZones_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

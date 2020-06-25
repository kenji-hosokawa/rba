/**
 * エリアセットクラスヘッダファイル
 */

#ifndef RBAAREASET_HPP
#define RBAAREASET_HPP

#include "RBAAllocatableSet.hpp"

namespace rba
{

class RBAArea;
class RBAAreaImpl;

class DLL_EXPORT RBAAreaSet : public RBAAllocatableSet
{
public:
  explicit RBAAreaSet(const std::string& name="");
  RBAAreaSet(const RBAAreaSet&)=delete;
  RBAAreaSet(const RBAAreaSet&&)=delete;
  RBAAreaSet& operator=(const RBAAreaSet&)=delete;
  RBAAreaSet& operator=(const RBAAreaSet&&)=delete;
  virtual ~RBAAreaSet()=default;

public:
  const std::list<const RBAArea*>& getTargets() const;
  void addTarget(const RBAAllocatable* alloc) override;
  void clear() override;
  RBAModelElementType getModelElementType() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAArea*> externAreas_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif

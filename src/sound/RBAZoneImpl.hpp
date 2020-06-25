/**
 * ゾーン実装クラスヘッダファイル
 */

#ifndef RBAZONEIMPL_HPP
#define RBAZONEIMPL_HPP

#include <cstdint>
#include <string>
#include "RBAAllocatable.hpp"
#include "RBAArbitrationPolicy.hpp"
#include "RBAZone.hpp"

namespace rba
{

class RBASoundContent;
class RBASoundContentImpl;

class RBAZoneImpl : public RBAZone, public RBAAllocatable
{
public:
  explicit RBAZoneImpl(const std::string& name="");
  RBAZoneImpl(const RBAZoneImpl&)=delete;
  RBAZoneImpl(const RBAZoneImpl&&)=delete;
  RBAZoneImpl& operator=(const RBAZoneImpl&)=delete;
  RBAZoneImpl& operator=(const RBAZoneImpl&&)=delete;
  virtual ~RBAZoneImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const std::list<const RBASoundContent*>& getContents() const override;
  RBAArbitrationPolicy getArbitrationPolicy() const override;

  void addContent(const RBASoundContentImpl* const content);
  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  std::string getSymbol() const override;
  std::string getHiddenSymbol() const override;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  mutable std::list<const RBASoundContent*> externContents_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  
};

}

#endif

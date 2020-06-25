/**
 * ゾーン実装クラス定義ファイル
 */

#include "RBASoundContentImpl.hpp"
#include "RBAZone.hpp"
#include "RBAArbitrationPolicy.hpp"
#include "RBAExpression.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAZoneImpl::RBAZoneImpl(const std::string& name)
  : RBARuleObject{name},
    RBAZone(),
    RBAAllocatable{name}
{
}

std::string
RBAZoneImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBAZoneImpl::getPriority() const
{
  //ZoneのPriorityは内部ではAreaのVisibilityと同じ扱い
  return getVisibility();
}

const std::list<const RBASoundContent*>&
RBAZoneImpl::getContents() const
{
  if(externContents_.size() == 0U) {
    for(const RBAContent* content : getInternalContents()) {
      externContents_.push_back(dynamic_cast<const RBASoundContentImpl*>(content));
    }
  }

  return externContents_;
}

RBAArbitrationPolicy
RBAZoneImpl::getArbitrationPolicy() const
{
  return getAllocatableArbitrationPolicy();
}

void
RBAZoneImpl::addContent(const RBASoundContentImpl* const content)
{
  RBAAbstractAllocatable::addContent(content);
}

RBAModelElementType
RBAZoneImpl::getModelElementType() const
{
  return RBAModelElementType::Zone;
}

#ifdef RBA_USE_LOG
std::string
RBAZoneImpl::getSymbol() const
{
  return "Zone";
}

std::string
RBAZoneImpl::getHiddenSymbol() const
{
  return "muted";
}
#endif

}


/**
 * サウンドコンテント実装クラス定義ファイル
 */

#include "RBASoundContentImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentImpl::RBASoundContentImpl(const std::string& name)
  : RBARuleObject{name},
    RBASoundContent(),
    RBAContent{name}
{
}

bool
RBASoundContentImpl::isSoundContent() const
{
  return true;
}

std::string
RBASoundContentImpl::getName() const
{
  return RBANamedElement::getElementName();
}

const std::list<const RBASoundContentState*>&
RBASoundContentImpl::getContentStates() const
{
  if(externStates_.size() == 0U) {
    for(const RBAContentState* state : getStates()) {
      externStates_.push_back(dynamic_cast<const RBASoundContentStateImpl*>(state));
    }
  }
  return externStates_;
}

const std::list<const RBAZone*>&
RBASoundContentImpl::getZones() const
{
  if(externZones_.size() == 0U) {
    for(const RBAAllocatable* allocatable : getAllocatables()) {
      externZones_.push_back(dynamic_cast<const RBAZoneImpl*>(allocatable));
    }
  }
  return externZones_;
}

RBAContentLoserType
RBASoundContentImpl::getLoserType() const
{
  return getContentLoserType();
}

RBAModelElementType
RBASoundContentImpl::getModelElementType() const
{
  return RBAModelElementType::SoundContent;
}

#ifdef RBA_USE_LOG
std::string
RBASoundContentImpl::getSymbol() const
{
  return "SoundContent";
}

std::string
RBASoundContentImpl::getVisibleSymbol() const
{
  return "sounding";
}
#endif

}

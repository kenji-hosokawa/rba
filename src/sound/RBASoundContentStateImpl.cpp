/**
 * 音声コンテントステート実装クラス定義ファイル
 */

#include "RBASoundContentStateImpl.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentStateImpl::RBASoundContentStateImpl(const std::string& name)
  : RBASoundContentState(),
    RBAContentState{name}
{
}

bool
RBASoundContentStateImpl::isSoundContentState() const
{
  return true;
}

std::string
RBASoundContentStateImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBASoundContentStateImpl::getPriority() const
{
  return getContentStatePriority();
}

const RBASoundContent*
RBASoundContentStateImpl::getOwner() const
{
  return dynamic_cast<const RBASoundContentImpl*>(RBARuleObject::getOwner());
}

std::int32_t
RBASoundContentStateImpl::getOrder() const
{
  return getContentStateOrder();
}

std::string
RBASoundContentStateImpl::getUniqueName() const
{
  return RBARuleObject::getOwner()->getUniqueName() + CONTEXT_SEPARATER + getName();
}

RBAModelElementType
RBASoundContentStateImpl::getModelElementType() const
{
  return RBAModelElementType::SoundContentState;
}

}

/**
 * ビューコンテントステート実装クラス定義ファイル
 */

#include "RBAViewContentImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAViewContentStateImpl::RBAViewContentStateImpl(const std::string& name)
  : RBAViewContentState(),
    RBAContentState{name}
{
}

std::string
RBAViewContentStateImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBAViewContentStateImpl::getPriority() const
{
  return getContentStatePriority();
}

const RBAViewContent*
RBAViewContentStateImpl::getOwner() const
{
  return dynamic_cast<const RBAViewContent*>(RBARuleObject::getOwner());
}

std::int32_t
RBAViewContentStateImpl::getOrder() const
{
  return getContentStateOrder();
}

std::string
RBAViewContentStateImpl::getUniqueName() const
{
  return RBARuleObject::getOwner()->getUniqueName() + CONTEXT_SEPARATER + getName();
}

bool
RBAViewContentStateImpl::isViewContentState() const
{
  return true;
}

RBAModelElementType
RBAViewContentStateImpl::getModelElementType() const
{
  return RBAModelElementType::ViewContentState;
}

}

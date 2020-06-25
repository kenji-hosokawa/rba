/**
 * ディスプレイ実装クラス定義ファイル
 */

#include "RBADisplayImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAAreaImpl.hpp"

namespace rba
{

RBADisplayImpl::RBADisplayImpl(const std::string& name)
  : RBADisplay(),
    RBANamedElement{name}
{
}

std::string
RBADisplayImpl::getName() const
{
  return RBANamedElement::getElementName();
}
  
const RBASize*
RBADisplayImpl::getSize() const
{
  return size_;
}

const std::list<const RBAArea*>&
RBADisplayImpl::getAreas() const
{
  return getAreaImpls();
}

void
RBADisplayImpl::setSize(const RBASizeImpl* const newSize)
{
  size_ = newSize;
}

void
RBADisplayImpl::addArea(const RBAAreaImpl* area)
{
  areas_.push_back(area);
}

const std::list<const RBAArea*>&
RBADisplayImpl::getAreaImpls() const
{
  return areas_;
}

}

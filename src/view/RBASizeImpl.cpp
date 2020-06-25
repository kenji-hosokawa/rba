/**
 * サイズ情報実装クラス定義ファイル
 */

#include "RBASizeImpl.hpp"

namespace rba
{

RBASizeImpl::RBASizeImpl(const std::string& name)
  : RBASize(),
    RBANamedElement{name}
{
}

std::string
RBASizeImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBASizeImpl::getWidth() const
{
  return width_;
}

std::int32_t
RBASizeImpl::getHeight() const
{
  return height_;
}

void
RBASizeImpl::setWidth(const std::int32_t newWidth)
{
  width_ = newWidth;
}

void
RBASizeImpl::setHeight(const std::int32_t newHeight)
{
  height_ = newHeight;
}

std::int32_t
RBASizeImpl::diff(const RBASizeImpl* const size) const
{
  std::int32_t w {width_ - size->getWidth()};
  if(w < 0) {
    w = -w;
  }
  std::int32_t h {height_ - size->getHeight()};
  if(h < 0) {
    h = -h;
  }

  return w + h;
}

}

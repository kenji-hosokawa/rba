/**
 * エリア実装クラス定義ファイル
 */

#include "RBAAreaImpl.hpp"

#include "RBAArbitrationPolicy.hpp"
#include "RBAContent.hpp"
#include "RBASizeImpl.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAAreaImpl::RBAAreaImpl(const std::string& name)
  : RBARuleObject{name},
    RBAArea(),
    RBAAllocatable{name}
{
}

std::string
RBAAreaImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBAAreaImpl::getX() const
{
  return x_;
}

std::int32_t
RBAAreaImpl::getY() const
{
  return y_;
}

std::int32_t
RBAAreaImpl::getZorder() const
{
  return zorder_;
}

const std::list<const RBAViewContent*>&
RBAAreaImpl::getContents() const
{
  if(externContents_.size() == 0U) {
    for(const RBAContent* const content : getInternalContents()) {
      if(content->isViewContent()) {
	const RBAViewContentImpl* contentImpl
	  {dynamic_cast<const RBAViewContentImpl*>(content)};
	externContents_.push_back(contentImpl);
      }
    }
  }

  return externContents_;
}

const std::list<const RBAViewContent*>&
RBAAreaImpl::getAllViewContents() const
{
  if(externAllContents_.size() == 0U) {
    for(const RBAViewContent* const content : getAllViewContentsRecursive(this)) {
      externAllContents_.push_back(content);
    }
  }

  return externAllContents_;
}

const std::list<const RBAViewContent*>
RBAAreaImpl::getAllViewContentsRecursive(const RBAAllocatable* const alloc) const
{
  std::list<const RBAViewContent*> contents;
  if(alloc == nullptr) {
    return contents;
  }

  for(const RBAContent* const content : alloc->getInternalContents()) {
    if(content->isViewContent()) {
      const RBAViewContentImpl* contentImpl	{dynamic_cast<const RBAViewContentImpl*>(content)};
      contents.push_back(contentImpl);
    }
    else {
      const RBAAllocatable* const a {dynamic_cast<const RBAAllocatable*>(content)};
      if(a != nullptr) {
        // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
        // 【ルールに逸脱している内容】
        // getAllViewContentsRecursive()を再帰呼び出ししている
        // 【ルールを逸脱しても問題ないことの説明】
        // CyclicContentが紐づいているAreaに対して、getAllViewContentsRecursive()したときは、
        // CyclicContentに紐づいているViewContentを含めて応答する動きになっている
        // CyclicContent に CyclicContent が割り当たる場合など、複数の再帰呼び出しが行われる可能性があるが、
        // ルールモデルの定義は有限であり、スタックオーバーフローすることはなく、問題無い
	for(const RBAViewContent* const c : getAllViewContentsRecursive(a)) {
	  contents.push_back(c);
	}
      }
    }
  }

  return contents;
}

const std::list<const RBASize*>&
RBAAreaImpl::getSizes() const
{
  return externSizes_;
}

RBAArbitrationPolicy
RBAAreaImpl::getArbitrationPolicy() const
{
  return getAllocatableArbitrationPolicy();
}

void
RBAAreaImpl::clearStatus()
{
  RBAAllocatable::clearStatus();
  resetCoordinate();
}

bool
RBAAreaImpl::isArea() const
{
  return true;
}

void
RBAAreaImpl::setZorder(const std::int32_t newZorder)
{
  zorder_ = newZorder;
}

void
RBAAreaImpl::setDefaultX(const std::int32_t defaultX)
{
  defaultX_ = defaultX;
  x_ = defaultX;
}

void
RBAAreaImpl::setDefaultY(const std::int32_t defaultY)
{
  defaultY_ = defaultY;
  y_ = defaultY;
}

void
RBAAreaImpl::setOffsetX(const std::int32_t offsetX)
{
  x_ = defaultX_ + offsetX;
}

void
RBAAreaImpl::setOffsetY(const std::int32_t offsetY)
{
  y_ = defaultY_ + offsetY;
}

void
RBAAreaImpl::addSize(const RBASizeImpl* size)
{
  externSizes_.push_back(size);
}

void
RBAAreaImpl::addContent(const RBAViewContentImpl* const content)
{
  RBAAbstractAllocatable::addContent(content);
}

void
RBAAreaImpl::resetCoordinate()
{
  x_ = defaultX_;
  y_ = defaultY_;
}

RBAModelElementType
RBAAreaImpl::getModelElementType() const
{
  return RBAModelElementType::Area;
}

#ifdef RBA_USE_LOG
std::string
RBAAreaImpl::getSymbol() const
{
  return "Area";
}

std::string
RBAAreaImpl::getHiddenSymbol() const
{
  return "hidden";
}
#endif

}

/**
 * 抽象アロケータブルクラス定義ファイル
 */

#include "RBAAbstractAllocatable.hpp"

#include "RBAModelElementType.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAViewContentSet.hpp"
#include "RBASoundContentSet.hpp"

namespace rba
{

RBAAbstractAllocatable::RBAAbstractAllocatable(const std::string& name)
  : RBARuleObject{name},
    contentSet_{std::make_unique<RBAContentSet>()}
{
}

const std::list<const RBAContent*>&
RBAAbstractAllocatable::getInternalContents() const
{
  return contentSet_->getLeafContent();
}

void
RBAAbstractAllocatable::addContent(const RBAContent* const content)
{
  contentSet_->addTarget(content);
}

const RBAContentSet*
RBAAbstractAllocatable::getContentSet() const
{
  return contentSet_.get();
}

}

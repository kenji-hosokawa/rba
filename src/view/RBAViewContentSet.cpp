/**
 * 表示コンテントセットクラス定義ファイル
 */

#include "RBAViewContentSet.hpp"
#include "RBAViewContent.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAViewContentSet::RBAViewContentSet(const std::string& name)
  : RBARuleObject{name},
    RBAContentSet{name}
{
}

const std::list<const RBAViewContent*>&
RBAViewContentSet::getTargets() const
{
  return externalContents_;
}

void
RBAViewContentSet::addTarget(const RBAContent* content)
{
  RBAContentSet::addTarget(content);
  externalContents_.push_back(dynamic_cast<const RBAViewContent*>(content));
}

void
RBAViewContentSet::clear()
{
  RBAContentSet::clear();
  externalContents_.clear();
}

RBAModelElementType
RBAViewContentSet::getModelElementType() const
{
  return RBAModelElementType::ViewContentSet;
}

}

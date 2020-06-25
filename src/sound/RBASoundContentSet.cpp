/**
 * 音声コンテントセットクラス定義ファイル
 */

#include "RBASoundContentSet.hpp"
#include "RBASoundContent.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentSet::RBASoundContentSet(const std::string& name)
  : RBARuleObject{name},
    RBAContentSet{name}
{
}

const std::list<const RBASoundContent*>&
RBASoundContentSet::getTargets() const
{
  return externalContents_;
}

void
RBASoundContentSet::addTarget(const RBAContent* content)
{
  RBAContentSet::addTarget(content);
  externalContents_.push_back(dynamic_cast<const RBASoundContent*>(content));
}

void
RBASoundContentSet::clear()
{
  RBAContentSet::clear();
  externalContents_.clear();
}

RBAModelElementType
RBASoundContentSet::getModelElementType() const
{
  return RBAModelElementType::SoundContentSet;
}

}

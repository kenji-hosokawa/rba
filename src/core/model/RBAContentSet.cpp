/**
 * コンテントセットクラス定義ファイル
 */

#include <string>
#include "RBAContentSet.hpp"
#include "RBAContent.hpp"

namespace rba
{

RBAContentSet::RBAContentSet(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractContent{name}
{
}

void
RBAContentSet::addTarget(const RBAContent* content)
{
  leafContent_.push_back(content);
#ifdef RBA_USE_LOG
  std::string newName = "[";
  for (auto& c : leafContent_) {
    newName += c->getElementName() + ",";
  }
  if (newName.size() != 1U) {
    newName.erase(newName.end() - 1);  // 末尾の,を削除する
  }
  newName += "]";
  setDynamicName(newName);
#endif
}

void
RBAContentSet::clear()
{
  leafContent_.clear();
#ifdef RBA_USE_LOG
  setDynamicName("[]");
#endif
}

const std::list<const RBAContent*>&
RBAContentSet::getLeafContent() const
{
  return leafContent_;
}

}

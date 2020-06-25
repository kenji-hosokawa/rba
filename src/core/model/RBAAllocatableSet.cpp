/**
 * アロケータブルセットクラス定義ファイル
 */

#include "RBAAllocatableSet.hpp"
#include "RBAAllocatable.hpp"

namespace rba
{

RBAAllocatableSet::RBAAllocatableSet(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractAllocatable{name}
{
}

void
RBAAllocatableSet::addTarget(const RBAAllocatable* alloc)
{
  leafAllocatable_.push_back(alloc);
#ifdef RBA_USE_LOG
  std::string newName = "[";
  for (auto& a : leafAllocatable_) {
    newName += a->getElementName() + ",";
  }
  if (newName.size() != 1U) {
    newName.erase(newName.end() - 1);  // 末尾の,を削除する
  }
  newName += "]";
  setDynamicName(newName);
#endif
}

void
RBAAllocatableSet::clear()
{
  leafAllocatable_.clear();
#ifdef RBA_USE_LOG
  setDynamicName("[]");
#endif
}

const std::list<const RBAAllocatable*>&
RBAAllocatableSet::getLeafAllocatable() const
{
  return leafAllocatable_;
}

}

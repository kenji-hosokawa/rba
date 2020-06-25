/**
 * AllInstanceOfSoundContentクラス定義ファイル
 */

#include "RBAAllInstanceOfSoundContent.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfSoundContent::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // For-All,Existsの集合にacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfSoundContent::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfSoundContent;
}

const RBARuleObject*
RBAAllInstanceOfSoundContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                                     RBAArbitrator* arb) const
{
  return &allSoundContentSet_;
}

void
RBAAllInstanceOfSoundContent::setContents(const std::list<const RBASoundContentImpl*>& contents)
{
  for(auto& cont : contents) {
    allSoundContentSet_.addTarget(cont);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfSoundContent::getExpressionText() const
{
  return "ALL_SOUNDCONTENTS";
}

const std::string
RBAAllInstanceOfSoundContent::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}

/**
 * AllInstanceOfViewContent実装クラス定義ファイル
 */

#include "RBAAllInstanceOfViewContent.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfViewContent::accept(RBAExpressionVisitor& visitor)
{
  // 現時点で唯一存在するvistorであるRBASceneAllocatableCollectorは、
  // For-All,Existsの集合にacceptしないのでこのパスを通ることはない。
  // 将来、別のvisitorがacceptするかもしれないので、残しておく。
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfViewContent::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfViewContent;
}

const RBARuleObject*
RBAAllInstanceOfViewContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                                    RBAArbitrator* arb) const
{
  return &allViewContentSet_;
}

void
RBAAllInstanceOfViewContent::setContents(const std::list<const RBAViewContentImpl*>& contents)
{
  for (auto& content : contents) {
    allViewContentSet_.addTarget(content);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfViewContent::getExpressionText() const
{
  return "ALL_VIEWCONTENTS";
}

const std::string
RBAAllInstanceOfViewContent::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}

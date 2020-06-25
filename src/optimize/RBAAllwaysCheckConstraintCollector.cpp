//
// RBAAllwaysCheckConstraintCollector.hpp
//

#include "RBAAllwaysCheckConstraintCollector.hpp"

#include "RBAConstraintImpl.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAAllwaysCheckConstraintCollector::RBAAllwaysCheckConstraintCollector(
    RBAModelImpl* const model)
    : RBAAbstractCollector{model}
{
}

void RBAAllwaysCheckConstraintCollector::init(
    const RBAConstraintImpl* const constraint)
{
  constraint_ = constraint;
  isAllways_ = false;
}

bool RBAAllwaysCheckConstraintCollector::isAllways() const
{
  return isAllways_;
}

void RBAAllwaysCheckConstraintCollector::visit(RBAPreviousModifier& exp)
{
  isAllways_ = true;
}

} /* namespace rba */

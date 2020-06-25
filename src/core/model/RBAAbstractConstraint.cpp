/**
 * 制約式の抽象クラス定義ファイル
 */

#include "RBAAbstractConstraint.hpp"

#include "RBAExpression.hpp"
#include "RBALogManager.hpp"

namespace rba
{

RBAAbstractConstraint::RBAAbstractConstraint(const std::string& name)
  : RBANamedElement{name}
{
}

bool
RBAAbstractConstraint::isConstraint() const
{
  return false;
}

bool
RBAAbstractConstraint::isRule() const
{
  return false;
}

void
RBAAbstractConstraint::clearInfo()
{
  info_->clear();
}

void
RBAAbstractConstraint::setExpression(RBAExpression* newExpr)
{
  expression_ = newExpr;
}

RBAExpression* const
RBAAbstractConstraint::getExpression() const
{
  return expression_;
}

RBAConstraintInfo*
RBAAbstractConstraint::getInfo() const
{
  return info_.get();
}

#ifdef RBA_USE_LOG
void
RBAAbstractConstraint::createHierarchy()
{
  LOG_initConstraintHierarchy();
  LOG_coverageHierarchyOfConstraintStartLog(this);
  getExpression()->createHierarchy();
  LOG_coverageHierarchyOfConstraintEndLog(this);
}
#endif

}

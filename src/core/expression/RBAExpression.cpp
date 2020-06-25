/**
 * 式クラス定義ファイル
 */

#include "RBAExpression.hpp"

#include "RBALetStatement.hpp"
#include "RBAConstraintInfo.hpp"
#ifdef RBA_USE_LOG
#include "RBAExpressionType.hpp"
#endif

namespace rba
{

void RBAExpression::addLetStatement(RBALetStatement* const letStatement)
{
  letStatements_.push_back(letStatement);
}

void
RBAExpression::accept(RBAExpressionVisitor& visitor)
{
  // 派生クラスの関数がコールされるため、コールされない
}

bool
RBAExpression::execute(RBAConstraintInfo* const info, RBAArbitrator * const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  const bool result {executeCore(info, arb)};
  if (result) {
    info->setResult(RBAExecuteResult::TRUE);
  } else {
    info->setResult(RBAExecuteResult::FALSE);
  }
  return result;
}

bool
RBAExpression::executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const
{
  // evaluate()でgetReferenceObject()を定義していないExpressionを
  // 指定した時、この関数がコールされる
  info->setExceptionBeforeArbitrate(true);
  return false;
}

const RBARuleObject*
RBAExpression::getReferenceObject(RBAConstraintInfo* const info,
                                      RBAArbitrator* const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  return getReferenceObjectCore(info, arb);
}

const RBARuleObject*
RBAExpression::getReferenceObjectCore(RBAConstraintInfo* info,
                                      RBAArbitrator* arb) const
{
  // evaluateObject()でgetReferenceObject()を定義していないExpressionを
  // 指定した時、この関数がコールされる
  return nullptr;
}

std::int32_t
RBAExpression::getValue(RBAConstraintInfo* const info, RBAArbitrator * const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  return getValueCore(info, arb);
}

const std::vector<RBALetStatement*>&
RBAExpression::getLetStatements() const
{
  return letStatements_;
}
std::int32_t
RBAExpression::getValueCore(RBAConstraintInfo* info, RBAArbitrator * arb) const
{
  // evaluateValue()でgetValue()を定義していないExpressionを
  // 指定した時、この関数がコールされる
  return -99;
}

void
RBAExpression::doAction(RBAConstraintInfo* const info, RBAArbitrator* const arb)
{
  info->setExpression(this);
  doActionCore(info, arb);
  return;
}

void
RBAExpression::doActionCore(RBAConstraintInfo* info, RBAArbitrator* arb)
{
  // evaluateDoAction()でdoAction()を定義していないExpressionを
  // 指定した時、この関数がコールされる
  return;
}

#ifdef RBA_USE_LOG
const std::string
RBAExpression::getExpressionText() const
{
  // 派生クラスの関数がコールされるため、コールされない
  return "Unsupported operation exception";
}

const std::string
RBAExpression::getCoverageExpressionText() const
{
  // 派生クラスの関数がコールされるため、コールされない
  return "Unsupported operation exception";
}

void
RBAExpression::createHierarchy()
{
  // 派生クラスの関数がコールされるため、コールされない
}

RBAExpressionType
RBAExpression::getUnderlyingType() const
{
  // 派生クラスの関数がコールされるため、コールされない
  return RBAExpressionType::EXCEPTION;
}
#endif

}

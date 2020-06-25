/*
 * Let式クラス定義ファイル
 */

#include "RBALetStatement.hpp"
#include "RBALogManager.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAModelElementType.hpp"
#include "RBAVariable.hpp"
#include "RBAExpressionVisitor.hpp"

namespace rba
{

RBAModelElementType RBALetStatement::getModelElementType() const
{
  return RBAModelElementType::LetStatement;
}

void RBALetStatement::setVariable(RBAVariable* const var)
{
  variable_ = var;
}

void
RBALetStatement::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

void RBALetStatement::setVariable(RBAArbitrator* const arb)
{
  RBAConstraintInfo* const info {variable_->createConstraintInfo()};
  variable_->setRuleObj(getLhsOperand()->getReferenceObject(info, arb));
#ifdef RBA_USE_LOG
  std::string valueName;
  if (info->isExceptionBeforeArbitrate() == true) {
    valueName = "before arbitrate skip";
  } else if (variable_->getRuleObj() == nullptr) {
    valueName = "NULL";
  } else {
    valueName = variable_->getRuleObj()->getElementName();
    if (valueName == "") {
      valueName = variable_->getRuleObj()->getDynamicName();
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      let " + variable_->getElementName() + " = "
          + getLhsOperand()->getExpressionText() + " = " + valueName);
#endif
}
} /* namespace rba */

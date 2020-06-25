/**
 * オペレータクラス定義ファイル
 */

#include "RBAOperator.hpp"
#include "RBALogManager.hpp"

namespace rba
{

const std::vector<RBAExpression*>&
RBAOperator::getOperand() const
{
  return operand_;
}

void
RBAOperator::addOperand(RBAExpression* const newExpr)
{
  if(newExpr != nullptr) {
    operand_.push_back(newExpr);
  }
}

RBAExpression*
RBAOperator::getLhsOperand() const
{
  return operand_.front();
}

RBAExpression*
RBAOperator::getRhsOperand() const
{
  return operand_.back();
}

const std::string
RBAOperator::getPreMsg(const bool isPrevious) const
{
  if(isPrevious) {
    return "(pre)";
  }
  else {
    return "";
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAOperator::getSymbol() const
{
  return "";
}

void
RBAOperator::createHierarchy()
{
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  std::uint32_t oprSize{ static_cast<std::uint32_t>(getOperand().size()) };
  if(oprSize == 1U) {
    RBAExpression* expr = getLhsOperand();
      expr->createHierarchy();
  }
  else {
    std::uint32_t num{ 0U };
    for(RBAExpression* expr : getOperand()) {
      // カバレッジ向けの制約階層構造に回数を追加
      LOG_addHierarchy("#" + std::to_string(num++));
      expr->createHierarchy();
      // カバレッジ向けの制約階層構造から回数を削除
      LOG_removeHierarchy();
    }
  }

  // カバレッジ向けの制約階層構造から回数を削除
  LOG_removeHierarchy();
}
#endif

}

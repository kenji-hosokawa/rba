/**
 * 論理オペレータクラス定義ファイル
 */

#include <sstream>
#include "RBALogicalOperator.hpp"
#include "RBAExpressionType.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string
RBALogicalOperator::getExpressionText() const
{
  std::ostringstream oss;
  oss << "(";
  const auto& exprList = getOperand();
  const auto& lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getExpressionText();
    if (expr != lastExpr) {
      oss << " " << getSymbol() << " ";
    }
  }
  oss << ")";

  return oss.str();
}

const std::string
RBALogicalOperator::getCoverageExpressionText() const
{
  std::ostringstream oss;
  oss << "(";
  auto exprList = getOperand();
  auto lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getCoverageExpressionText();
    if (expr != lastExpr) {
      oss << " " << getSymbol() << " ";
    }
  }
  oss << ")";

  return oss.str();
}

RBAExpressionType
RBALogicalOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}

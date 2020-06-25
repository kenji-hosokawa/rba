/**
 * コンテントオペレータクラス定義ファイル
 */

#include "RBAContentOperator.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string
RBAContentOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string
RBAContentOperator::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}
#endif

}

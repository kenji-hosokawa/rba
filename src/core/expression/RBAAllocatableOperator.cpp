/**
 * Allcatable operator class definitio
 */

#include "RBAAllocatableOperator.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string
RBAAllocatableOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string
RBAAllocatableOperator::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}
#endif

}

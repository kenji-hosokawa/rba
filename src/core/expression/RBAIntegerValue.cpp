/**
 * 整数値クラス定義ファイル
 */

#include "RBAIntegerValue.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"

namespace rba
{

void
RBAIntegerValue::setValue(const std::int32_t value)
{
  value_ = value;
}

std::int32_t
RBAIntegerValue::getValue() const
{
  return value_;
}

RBAModelElementType
RBAIntegerValue::getModelElementType() const
{
  return RBAModelElementType::IntegerValue;
}

std::int32_t
RBAIntegerValue::getValueCore(RBAConstraintInfo* info, RBAArbitrator * arb) const
{
  return getValue();
}

#ifdef RBA_USE_LOG
const std::string
RBAIntegerValue::getExpressionText() const
{
  return std::to_string(value_);
}

const std::string
RBAIntegerValue::getCoverageExpressionText() const
{
  return getExpressionText();
}

void
RBAIntegerValue::createHierarchy()
{
  // このExpression以下にHierarchyは存在しないので、何もしない
}

RBAExpressionType
RBAIntegerValue::getUnderlyingType() const
{
  return RBAExpressionType::VALUE;
}
#endif

}
